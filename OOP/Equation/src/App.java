public class App {
    public static void main(String[] args) {
        EqDegOne eq = new EqDegOne(0, 2);
        System.out.println(eq.isSolved());
        System.out.println(eq.solve());
    }
}
