import valuables.Gemstone;
import safes.Safe;

public class App {
    public static void main(String[] args) throws Exception {
        Gemstone gem1 = new Gemstone(1d);
        Gemstone gem2 = new Gemstone(2d);
        Gemstone gem3 = new Gemstone(3d);

        Safe mySafe = new Safe(3);

        mySafe.addGem(gem1);
        mySafe.addGem(gem2);
        mySafe.addGem(gem3);

        System.out.println(gem1.getValue());
        System.out.println(gem2.getValue());
        System.out.println(gem3.getValue());

        System.out.println(mySafe.getValue());

        mySafe.removeGem(gem3);

        System.out.println(mySafe.getValue());

        mySafe.addGem(gem3);
        mySafe.addGem(gem3);

        System.out.println(mySafe.getValue());

    }
}
