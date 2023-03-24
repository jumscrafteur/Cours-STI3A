# Aide Instalation Gentoo                                    My Gentoo handbook
> created with the help of [@AnPatapain](https://github.com/AnPatapain/lean-gentoo-handbook) guide                
### Initial set up: 
- ram 2gb
- disk 30gb
- other linux 5x kernel


## Step 1: Network test + ssh connection:

```
$ ping -c 3 www.google.com
$ passwd
<your-password>

$ /etc/init.d/sshd start
$ ifconfig
```

## Step 2: SSH connection
```
[INSA] $ ssh root@<ip>
```

## Step 3: disk partition
```
$ cfdisk /dev/sda
```
1. Select DOS
2. Configuration des partitions *( peut changer )*
    ``` 
    /dev/sda1: new -> primary -> 600M -> boot flag
    /dev/sda2: new -> extended -> 22G 
    in /dev/sda2
        /dev/sda5: new -> 18G
        /dev/sda6: new -> 2G
        /dev/sda7: new -> 2gb
    in Free space:
        /dev/sda3: new -> 1.5G -> 82 linux swap / solaris

    ```
3. write and quit
```
$ fdisk -l
Device     Boot    Start      End  Sectors  Size Id Type
/dev/sda1  *        2048  1230847  1228800  600M 83 Linux
/dev/sda2        1230848 47368191 46137344   22G  5 Extended
/dev/sda3       47368192 50513919  3145728  1.5G 82 Linux swap / Solaris
/dev/sda5        1232896 38981631 37748736   18G 83 Linux
/dev/sda6       38983680 43177983  4194304    2G 83 Linux
/dev/sda7       43180032 47368191  4188160    2G 83 Linux
```
## Step 4: Create file system
```
$ mke2fs /dev/sda1
$ mke2fs -j /dev/sda5
$ mkswap /dev/sda3 && swapon /dev/sda3
$ mount /dev/sda5 /mnt/gentoo
$ mkdir /mnt/gentoo/boot
$ mount /dev/sda1 /mnt/gentoo/boot
$ cd /mnt/gentoo
```
## Step 5: stage 3 installation

window :
```
[INSA] $ scp .\stage3-amd64-openrc-....tar.xz root@<ip>:/mnt/gentoo 
```

check whether the stage is successfully sent 
```
$ ls
boot  lost+found  stage3-amd64-openrc-....tar.xz
```
extract: 
```
$ time tar -xf stage3...
```
check: 
```
$ ls
bin   dev  home  lib64       media  opt   root  sbin                                         sys  usr
boot  etc  lib   lost+found  mnt    proc  run   stage3-amd64-openrc-20221106T170545Z.tar.xz  tmp  var
```

## Step 6: Chroooting + update env variables
```
$ cd /
$ mount -t proc none /mnt/gentoo/proc
$ mount -o bind /dev /mnt/gentoo/dev
$ cp -L /etc/resolv.conf /mnt/gentoo/etc/
$ chroot /mnt/gentoo /bin/bash
$ env-update && source /etc/profile
```


## Step 7: Now the command will affect directly on your machine as root. Set up hosts.
```
$ nano -w /etc/hosts
127.0.0.1   <your-host-name> localhost

$ nano -w /etc/conf.d/hostname
hostname="<your-host-name>"

$ hostname <your-host-name>
$ hostname -f
<your-host-name>
```
## Step 8: Config etc/fstab to auto mount at boot
```
$ nano -w /etc/fstab
/dev/sda1               /boot           ext2            noauto,noatime  1 2
/dev/sda5               /               ext3            noatime         0 1
/dev/sda3               none            swap            sw              0 0
```
## Step 9: change password
```
$ passwd
<your-password>
```

## Step 10: loadmap
```
$ nano -w /etc/conf.d/keymaps
```
- put `KEYMAP='fr'`

## Step 10: Install base system so that the minimal environment is available for your pc
```
[INSA] $ scp .\portage-latest.tar.bz2 root@<ip>:/mnt/gentoo/usr/
$ cd /usr
$ time tar xjpf portage-...
$ env-update
$ ln -s /usr/portage /var/db/repos/gentoo
$ env-update
```

# Step 11:
```
[INSA] $ scp .\distfiles.tar.bz2 root@<ip>:/mnt/gentoo/var/cache
```

```
$ cd /var/cache
$ time tar xjpf distfiles...
```

```
[INSA] $ scp .\packages.tar.bz2 root@<ip>:/mnt/gentoo/var/cache
```

```
$ time tar xjpf packages.tar.bz2
```

## Step 12: the most important part, install KERNEL, cronie, dhcpcd, bootloader grub, config grub

```
$ emerge -K gentoo-kernel-bin
$ emerge -K cronie
$ emerge -K dhcpcd
$ emerge -K grub:2
$ emerge -K syslog-ng
$ grub-install /dev/sda
$ grub-mkconfig -o /boot/grub/grub.cfg
```
## Step 13: reboot
```
$ exit
$ umount /mnt/gentoo/proc /mnt/gentoo/boot /mnt/gentoo/dev /mnt/gentoo
```
- Reponse possible :
    ```
    umount: /mnt/gentoo: target is busy
    ```

## Step 14: 
1. power off 
2. edit machine
3. cd
4. choose physical disk auto detect

## Step 15: 
```
$ nano -w /etc/ssh/sshd_config
```
- put `PermitRootLogin yes`

```
$ ping -c 3 www.google.com      
```
## Step 16: 3. Utilisateurs
```
$ useradd -m -G users,wheel exam1
```
- Erreur possible
    ```
    Creating mailbox file: No such file or directory
    ```

```
$ passwd exam1
<your-user-password>

$ /etc/init.d/sshd restart
```

```
[INSA] $ ssh exam1@<ip>
```
## Step 17: 4. Gestion des services
```
$ emerge -K syslog-ng
$ emerge -av sys-process/cronie
$ rc-update add cronie default
$ rc-update add syslog-ng default
```

Test whether cronie were installed properly
```
$ qlist -e cronbase | grep bin
/usr/sbin/run-crons 
```
Test cronie by run "date" and send the date to test_cron.txt every 1 minute:
```
$ cd /home
$ touch test_cron.txt
$ crontab -e 
```
- put `* * * * * date >> /home/test_cron.txt`
```
$ /etc/init.d/cronie restart
$ cat test.txt
Wed Mar 22 01:13:01 -00 2023
Wed Mar 22 01:14:01 -00 2023
...
Wed Mar 22 01:14:01 -00 2023

```
Back to requirements of exam. 
Configurer syslog-ng pour mettre tous les messages venant de login dedans "/var/log/login.log"
```
$ nano -w /etc/syslog-ng/syslog-ng.conf

******************/etc/syslog-ng/syslog-ng.conf********************
*                                                                 *
* destination loginLog { file("/var/log/login.log"); };           *                    
* filter f_login { facility(auth); };                             *
* log { source(src); filter(f_login); destination(loginLog); };   *
*                                                                 *
*******************************************************************
```
TO TEST: 
```
$ reboot
$ cat /var/log/login.log
log...

$ cd /home 
$ mkdir backup
$ mkdir backup/data
$ mkdir /mnt/backup
$ nano /etc/cron.d/backup.sh
20 15 * * * root /bin/tar czf /mnt/backup/data.tar.gz /home/backup/data
```
- Ne pas oublier de changer l'heure du cron pour tester
```
$ chmod 755 /etc/cron.d/backup.sh
$ /etc/init.d/cronie restart
```
```
$ ls /mnt/backup
data.tar.gz
```
Install apache & proftpd. Don't forget -K ?
```
$ emerge apache
$ rc-update add apache2 default
$ /etc/init.d/apache2 start
```
You will probably have error about credential
This is the guide how to fix it by adding credential for apache2.
```
$ cd /etc/ssl
```
generate new ssl key&cert
```
$ openssl req -newkey rsa:4096 \
    -x509 \
    -sha256 \
    -days 3650 \
    -nodes \
    -out example.crt \
    -keyout example.key
```
type whatever you want on the generating step
```
$ nano -w /etc/apache2/vhosts.d/00_default_ssl_vhost.conf
```
inside find the 2 ssl line and replace with:
```
_________________________________________________________
SSLCertificateFile /etc/ssl/example.crt

SSLCertificateKeyFile /etc/ssl/example.key 
___________________________________________________________
```
```
$ /etc/init.d/apache2 start
```
Now the apache should start properly !

```
$ emerge -K proftpd
$ rc-update add proftpd default
```
You must create config file for proftpd in order to be able start the service
```
$ cat /etc/proftpd/proftpd.conf.sample
$ cp /etc/proftpd/proftpd.conf.sample /etc/proftpd/proftpd.conf
$ /etc/init.d/proftpd start
```
## Step 18: Check services
```
$ reboot
$ /etc/init.d/cronie status
$ /etc/init.d/apache2 status
$ /etc/init.d/proftpd status
```
RAID + LVM
```
$ emerge sys-fs/mdadm
$ modprobe dm-mod
$ emerge -K lvm2
```
Create raid 1 array
```
$ mdadm --create /dev/md0 --level=1 --raid-devices=2 /dev/sda6 /dev/sda7
```
Prepare raid array for Volume Group
```
$ pvcreate /dev/md0
```
Create Volume Group VG1 using raid array 
```
$ vgcreate VG1 /dev/md0
```
- check 
    ``` 
    $ pvdisplay
    $ vgdisplay
    ```

Create logical volume named "backup" and make file system
```
$ lvcreate -L 0.9G -n backup VG1
$ mkfs.ext3 /dev/VG1/backup
```
Mount /dev/VG1/backup to /backup
```
$ mkdir /backup
$ mount /dev/VG1/backup /backup
```
Create logical volume named "data" and make file system
```
$ lvcreate -L 0.9G -n data VG1
$ mkfs.ext3 /dev/VG1/data
```
Mount /dev/VG1/data to /data
```
$ mkdir /data
$ mount /dev/VG1/data /data
```
Automatically mount at reboot
```
$ nano -w /etc/fstab
-------------------------------------------------------
/dev/VG1/backup  /backup ext3 defaults 0 0
/dev/VG1/data  /data ext3 defaults 0 0
-------------------------------------------------------
```

## Final:
```
$ cd /root
$ touch evaluation.sh
$ nano evaluation.sh
```
ctrl c & ctrl v
```
$ chmod 777 evaluation.sh
$ ./evaluation.sh
```
On power shell, go to enseignement
Don't forget "." at the end. That means send to the current location.
```
[INSA] $ scp root@<ip>:/tmp/evaluation.tar.bz2 .
```

<!-- Some funny stuffs:
	rotate the login.log:
		>> cd /etc/logrotate.d
		>> nano auth-message-rotate
		/var/log/login.log {
			daily
        		rotate 7
        		compress
        		delaycompress
        		missingok
		}
		in /etc/logrotate.conf there is a directive: "include /etc/logrotate.d" 		so all files in /etc/logrotate.d will be executed automatically

		>> logrotate -f /etc/logrotate.conf
		
	Archive /etc to /var/backup as etc-DATE.zip every night
	>> mkdir /var/backup
	>> emerge zip
	>> nano -w /etc/cron.daily/etc-backup
	#!/bin/bash

	BACKUP_DIR="/var/backup"

	DATE=$(date +%d-%m-%Y)

	cd / && zip -r "$BACKUP_DIR/etc-$DATE.zip" etc
	>> chmod +x /etc/cron.daily/etc-backup

@version: 3.17        #mandatory since Version 3, specify the version number of the used syslog-ng
     
options {
        chain_hostnames(no);

        # The default action of syslog-ng is to log a STATS line
        # to the file every 10 minutes.  That's pretty ugly after a while.
        # Change it to every 12 hours for a nice daily update of
        # how many messages syslog-ng missed (0).
        stats_freq(43200);
};

source src {
    unix-stream("/dev/log" max-connections(256));
    internal();
};

source kernsrc { file("/proc/kmsg"); };

# define destinations
destination authlog { file("/var/log/auth.log"); };
destination syslog { file("/var/log/syslog"); };
destination cron { file("/var/log/cron.log"); };
destination daemon { file("/var/log/daemon.log"); };
destination kern { file("/var/log/kern.log"); };
destination lpr { file("/var/log/lpr.log"); };
destination user { file("/var/log/user.log"); };
destination mail { file("/var/log/mail.log"); };

destination mailinfo { file("/var/log/mail.info"); };
destination mailwarn { file("/var/log/mail.warn"); };
destination mailerr { file("/var/log/mail.err"); };

destination newscrit { file("/var/log/news/news.crit"); };
destination newserr { file("/var/log/news/news.err"); };
destination newsnotice { file("/var/log/news/news.notice"); };

destination debug { file("/var/log/debug"); };
destination messages { file("/var/log/messages"); };
destination console { usertty("root"); };

# By default messages are logged to tty12...
destination console_all { file("/dev/tty12"); };

# ...if you intend to use /dev/console for programs like xconsole
# you can comment out the destination line above that references /dev/tty12
# and uncomment the line below.
#destination console_all { file("/dev/console"); };

# create filters
filter f_authpriv { facility(auth, authpriv); };
filter f_syslog { not facility(authpriv, mail); };
filter f_cron { facility(cron); };
filter f_daemon { facility(daemon); };
filter f_kern { facility(kern); };
filter f_lpr { facility(lpr); };
filter f_mail { facility(mail); };
filter f_user { facility(user); };
filter f_debug { not facility(auth, authpriv, news, mail); };
filter f_messages { level(info..warn)
        and not facility(auth, authpriv, mail, news); };
filter f_emergency { level(emerg); };

filter f_info { level(info); };
filter f_notice { level(notice); };
filter f_warn { level(warn); };
filter f_crit { level(crit); };
filter f_err { level(err); };
filter f_failed { message("failed"); };
filter f_denied { message("denied"); };

# connect filter and destination
log { source(src); filter(f_authpriv); destination(authlog); };
log { source(src); filter(f_syslog); destination(syslog); };
log { source(src); filter(f_cron); destination(cron); };
log { source(src); filter(f_daemon); destination(daemon); };
log { source(kernsrc); filter(f_kern); destination(kern); };
log { source(src); filter(f_lpr); destination(lpr); };
log { source(src); filter(f_mail); destination(mail); };
log { source(src); filter(f_user); destination(user); };
log { source(src); filter(f_mail); filter(f_info); destination(mailinfo); };
log { source(src); filter(f_mail); filter(f_warn); destination(mailwarn); };
log { source(src); filter(f_mail); filter(f_err); destination(mailerr); };

log { source(src); filter(f_debug); destination(debug); };
log { source(src); filter(f_messages); destination(messages); };
log { source(src); filter(f_emergency); destination(console); };

# default log
log { source(src); destination(console_all); };

















 -->
