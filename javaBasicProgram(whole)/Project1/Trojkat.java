public class Trojkat implements inter{

    public String typ = "Trojkat";

    @Override
    public String typ() {
        return typ;
    }

    @Override
    public void draw(double a,double h) {
        double belka = a/h;

        for(int i=0; i<=h-1;i++) {
            for (int j = 0; j <= belka; j++)
                System.out.print("X");
            System.out.println();
            if(belka<=a)
                belka+=(a/h) ;
        }
    }

    public void draw(double a) {
        System.out.println("Podano tylko 1 parametr");
    }
}
