package geometrie;

public class GeometricalShape {

  protected String color = "";
  private String texture = "";

  public GeometricalShape(String color, String texture) {
    this.color = color;
    this.texture = texture;
  }

  public GeometricalShape() {

  }

  public String getColor() {
    return color;
  }

  public void setColor(String color) {
    this.color = color;
  }

  public String getTexture() {
    return texture;
  }

  public void setTexture(String texture) {
    this.texture = texture;
  }

  public void draw(int zone) {
    System.out.println(String.format("Drawing the %d th zone of a shape", zone));
  }

  public void draw(Point p) {
    System.out.println("Drawing a rectangle");
  }

  public void draw() {
    System.out.println("Drawing a shape");
  }

}
