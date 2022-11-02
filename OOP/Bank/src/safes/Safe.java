package safes;

import java.util.ArrayList;

import valuables.Gemstone;

public class Safe {
  private int currentGemsNb = 0;
  final int capacity;
  private boolean opened = false;
  private ArrayList<Gemstone> myContent = new ArrayList<Gemstone>();

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

    this.currentGemsNb++;
    gemstone.setMySafe(this);
    myContent.add(gemstone);

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

    for (Gemstone gemstone : myContent) {
      sum += gemstone.getValue();
    }

    return sum;
  }

}
