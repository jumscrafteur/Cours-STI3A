package safes;

import java.util.Iterator;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

import valuables.Gemstone;
import valuables.NotExpertisedException;

public class Safe {
  private int currentGemsNb = 0;
  final int capacity;
  private boolean opened = false;

  private TreeMap<Gemstone, TreeSet<Gemstone>> myContent = new TreeMap<Gemstone, TreeSet<Gemstone>>();

  /**
   * 
   * @param capacity
   */
  public Safe(int capacity) {
    this.capacity = capacity;
  }

  public void open() {
    if (this.opened)
      System.err.println("Safe already opened");
    this.opened = true;
  }

  public void close() {
    if (!this.opened)
      System.err.println("Safe already closed");
    this.opened = false;
  }

  /**
   * 
   * @param gemstone
   */
  public void addGem(Gemstone gemstone) {
    if (gemstone.getMySafe() != null) {
      System.err.println("Gemstone already in a safe");
      return;
    }

    if (!this.opened) {
      System.err.println("The Safe is closed");
      return;
    }

    if (this.isFull()) {
      System.err.println("The safe is full");
      return;
    }

    Set<Gemstone> keys = myContent.keySet();

    if (keys.contains(gemstone)) {
      TreeSet<Gemstone> equSet = myContent.get(gemstone);
      equSet.add(gemstone);
    } else {
      // TreeSet<Gemstone> equSet = new TreeSet();
      // myContent.put(gemstone)

    }

  }

  /**
   * 
   * @param gemstone
   */
  public void removeGem(Gemstone gemstone) {
    if (!this.opened) {
      System.err.println("The Safe is closed");
      return;
    }

    if (this.myContent.contains(gemstone)) {
      System.err.println("The gemstone is not in the safe");
      return;
    }

    this.currentGemsNb--;
    gemstone.setMySafe(null);
    myContent.remove(gemstone);

  }

  /**
   * 
   * @return
   */
  public boolean isFull() {
    return this.capacity == this.currentGemsNb;
  }

  /**
   * 
   * @return
   */
  public double getValue() {
    double sum = 0;

    Iterator<Gemstone> iterator = myContent.iterator();

    while (iterator.hasNext()) {
      try {
        sum += iterator.next().getValue();
      } catch (NotExpertisedException e) {
        iterator.next().expertize();
        // e.printStackTrace();
      }
    }

    return sum;
  }

}
