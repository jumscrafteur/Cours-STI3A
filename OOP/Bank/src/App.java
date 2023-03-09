import valuables.Gemstone;
import safes.Safe;

public class App {
    public static void main(String[] args) throws Exception {
        Gemstone gem1 = new Gemstone(1d);

        System.out.println(gem1.getValue());

    }
}
