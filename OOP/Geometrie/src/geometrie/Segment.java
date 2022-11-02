package geometrie;

public class Segment {

	private Point start = new geometrie.Point();
	private Point end = new geometrie.Point();

	public Segment(Point start, Point end) {
		this.start = start;
		this.end = end;
		System.out.println("A line segment has been created");
	}

	public Point getStart() {
		return start;
	}

	public void setStart(Point start) {
		this.start = start;
	}

	public Point getEnd() {
		return end;
	}

	public void setEnd(Point end) {
		this.end = end;
	}

	public double length() {
		return start.distance(end);
	}

	@Override
	public String toString() {
		return "[" + start.getLabel() + end.getLabel() + "]";
	}

}
