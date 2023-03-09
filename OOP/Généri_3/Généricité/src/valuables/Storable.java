package valuables;

import safes.GenericSafe;

public interface Storable<T1> {

  public abstract void setMyContainer(T1 Container);

  public abstract T1 getMyContainer();
}
