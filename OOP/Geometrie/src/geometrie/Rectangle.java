package geometrie;

public class Rectangle extends Quadrilateral {
  public Rectangle(Point p1, Point p4) {
    super(p1, new Point(p4.getX(), p1.getY()), p4, new Point(p1.getX(), p4.getX()));
  }

  public Rectangle() {
    // System.out.println("Rectangle Constructor");
  }

  public double getPerimeter() {
    Segment[] segs = this.getTheSegments();
    System.out.println("Computing the perimeter of a rectangle");

    return 2 * (segs[0].length() + segs[1].length());
  }

}
