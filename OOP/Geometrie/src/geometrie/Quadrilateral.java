package geometrie;

public class Quadrilateral extends Polygon {

	private Segment[] theSegments = new Segment[4];

	public Quadrilateral(Point p1, Point p2, Point p3, Point p4) {
		theSegments[0] = new Segment(p1, p2);
		theSegments[1] = new Segment(p2, p3);
		theSegments[2] = new Segment(p3, p4);
		theSegments[3] = new Segment(p4, p1);
		// System.out.println("Quadrilateral");
	}

	public Quadrilateral() {
		this(new Point(), new Point(), new Point(), new Point());
	}

	public Segment[] getTheSegments() {
		return theSegments;
	}

	public void setLesSegments(Segment[] theSegments) {
		this.theSegments = theSegments;
	}

	public double getPerimeter() {
		double perimeter = 0;

		System.out.println("Computing the perimeter of a quadrilateral");

		perimeter = theSegments[0].length() + theSegments[1].length()
				+ theSegments[2].length() + theSegments[3].length();
		return perimeter;
	}

	public String toString() {
		return theSegments[0] + " " + theSegments[1] + " " + theSegments[2] + " " + theSegments[3];
	}

}
