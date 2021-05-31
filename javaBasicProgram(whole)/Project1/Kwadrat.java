public class Kwadrat implements inter {
    public String typ = "Kwadrat";

    @Override
    public String typ() {
        return typ;
    }

    @Override
    public void draw(double a) {
        for (int i = 0; i <= a; i++) {
            for (int j = 0; j <= a; j++)
                System.out.print("X");
            System.out.println();
        }
    }

    public void draw(double a,double b) {
        System.out.println("Podano tylko 2 parametry");
    }

}