/**
 * Free to reuse
 */
package safes;

import valuables.*;

import java.util.ArrayList;

public class GenericSafe<T1 extends Valuable & Storable<GenericSafe<T1>>>
		implements Valuable, Storable<GenericSafe<GenericSafe<T1>>> {

	private final int capacity;
	private int currObjNb = 0;
	protected boolean opened = true;
	protected int value = 0;
	private ArrayList<T1> myContent = new ArrayList<T1>();
	private GenericSafe<GenericSafe<T1>> myContainer;

	public GenericSafe() {
		capacity = 1;
		System.out.println("Default safe constructor");
	}

	public GenericSafe(int capac) {
		capacity = capac;
		System.out.println("Safe constructor with capacity");
	}

	protected double sum() {
		double sum = 0;

		for (T1 d : this.myContent)
			if (d.getValue() == -1) {
				System.err.println("erreur expertize");
			} else {
				sum += d.getValue();
			}

		return sum;
	}

	public double getValue() {

		double value = 0;
		value = sum();
		return value;
	}

	public int getCapacity() {
		return capacity;
	}

	public boolean isOpened() {
		return opened;
	}

	public void open() {
		if (opened)
			System.err.println("Trying to open an opened safe...");
		this.opened = true;
	}

	public void close() {
		if (!isOpened())
			System.err.println("Trying to close a closed safe...");
		this.opened = false;
	}

	public ArrayList<T1> getMyContent() {
		return myContent;
	}

	public boolean isFull() {
		return this.currObjNb == this.capacity;
	}

	public void addObject(T1 object) {

		if (!opened)
			System.err.println("Impossible to add a object; the safe is closed!");
		// Is it full?
		else if (isFull())
			System.err.println("Impossible to add a object; the safe is full!");

		else if (object.getMyContainer() != null)
			System.err.println("Impossible to add a object; it's already in another safe!");

		else {
			myContent.add(object);
			object.setMyContainer(this);
			this.currObjNb++;
		}
	}

	/**
	 * Removes a object from the safe
	 * 
	 * @param object the object to remove
	 */

	public void removeObject(T1 object) {
		// Testing whether we can remove the object
		// Is the safe opened?
		if (!opened)
			System.err.println("Impossible to remove object; the safe is closed!");
		// Good to go!
		else {
			if (myContent.remove(object)) {
				object.setMyContainer(null);
				this.currObjNb--;
			} else {
				System.err.println("Impossible to remove the specified object; it is not in the safe!");
			}
		}
	}

	public void setMyContainer(GenericSafe<GenericSafe<T1>> Container) {
		this.myContainer = Container;
	}

	public GenericSafe<GenericSafe<T1>> getMyContainer() {
		return myContainer;
	}
}