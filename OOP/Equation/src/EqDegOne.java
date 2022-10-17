
public class EqDegOne {
    private float a = 0;
    private float b = 0;
    private float solution;
    private boolean solved = false;

    public EqDegOne(float iniA, float iniB) {
        this.a = iniA;
        this.b = iniB;
    }

    public boolean isSolved() {
        return this.solved;
    }

    public void setA(float newA) {
        if (this.a != newA) {
            this.a = newA;
            this.solved = false;
        }
    }

    public void setB(float newB) {
        if (this.b != newB) {
            this.b = newB;
            this.solved = false;
        }
    }

    public Float solve() {
        if (!isInversible(a)) {
            System.err.println("a (" + this.a + ") is not inversible");
            return null;
        }

        if (!this.solved)
            this.solution = -this.b / this.a;

        return this.solution;
    }

    private boolean isInversible(float x) {
        return x != 0;
    }
}
