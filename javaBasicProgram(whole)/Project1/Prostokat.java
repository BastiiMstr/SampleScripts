public class Prostokat implements inter{
    String typ = "Prostokat";

    @Override
    public String typ() {
        return typ;
    }

    @Override
    public void draw(double a, double b) {
        for(int i=0; i<=a;i++) {
            for (int j = 0; j <= b; j++)
                System.out.print("X");
        System.out.println();
        }
    }

    @Override
    public void draw(double a) {
        System.out.println("Podano tylko 1 parametr");
    }
}
