/**
 * 
 */
package test;

import safes.*;
import valuables.*;

/**
 * @author ceichler
 *
 */
public class TestSafe {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		GenericSafe<GenericSafe<Gemstone>> gsg = new GenericSafe<GenericSafe<Gemstone>>(5);

	}

}