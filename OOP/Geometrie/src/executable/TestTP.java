package executable;

import geometrie.*;

public class TestTP {

	public static void main(String[] args) {
		Point p1 = new Point(1, 1, "A");
		Point p2 = new Point(2, 2, "B");

		Segment seg1 = new Segment(p1, p2);
		System.out.println(seg1.length());
	}

}
