package executable;

import geometrie.*;

public class TestTP {

	public static void main(String[] args) {
		// Question 1.b

		// Rectangle r = new Rectangle();
		// r.draw(4);
		// r.draw();
		// r.draw(new Point());

		// Question 1.d

		// Quadrilateral quad = new Quadrilateral();
		// double perquad = quad.getPerimeter();

		// quad = new Rectangle();
		// double perrect = quad.getPerimeter();

		// Question 1.f

		// GeometricalShape[] listFig = new GeometricalShape[3];
		// listFig[0] = new Rectangle();

		// listFig[1] = new Quadrilateral();
		// listFig[2] = new Ellipse();

		// Question 1.g

		// Rectangle rec = new Quadrilateral();

		// Question 1.h

		GeometricalShape[] listFig = new GeometricalShape[3];
		listFig[0] = new Rectangle();
		listFig[1] = new Quadrilateral();
		listFig[2] = new Ellipse();
		for (int i = 0; i <= 2; i++) {
			listFig[i].draw();
		}
		listFig[0].getPerimeter();
	}

}
