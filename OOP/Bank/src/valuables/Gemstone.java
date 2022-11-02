package valuables;

import safes.Safe;

public class Gemstone {
  private double value = -1;
  final double volume;
  private Safe mySafe;

  /**
   * 
   * @param myVolume
   */
  public Gemstone(double myVolume) {
    volume = myVolume;
  }

  public void expertize() {
    value = volume * 100;
  }

  /**
   * 
   * @return
   */
  public Safe getMySafe() {
    return mySafe;
  }

  /**
   * 
   * @param mySafe
   */
  public void setMySafe(Safe mySafe) {
    this.mySafe = mySafe;
  }

  /**
   * 
   * @return
   */
  public double getValue() {
    if (this.value == -1) {
      this.expertize();
    }
    return value;
  }

  /**
   * 
   * @return
   */
  public double getVolume() {
    return volume;
  }

}
