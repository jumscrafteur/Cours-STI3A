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
   * @throws NotExpertisedException
   */
  public double getValue() throws NotExpertisedException {
    if (this.value == -1)
      throw new NotExpertisedException("Gemstone not expertized");

    return value;
  }

  /**
   * 
   * @return
   */
  public double getVolume() {
    return volume;
  }

  @Override
  public int hashCode() {
    final int prime = 31;
    int result = 1;
    long temp;
    temp = Double.doubleToLongBits(volume);
    result = prime * result + (int) (temp ^ (temp >>> 32));
    return result;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (obj == null)
      return false;
    if (getClass() != obj.getClass())
      return false;
    Gemstone other = (Gemstone) obj;
    if (Double.doubleToLongBits(volume) != Double.doubleToLongBits(other.volume))
      return false;
    return true;
  }
}
