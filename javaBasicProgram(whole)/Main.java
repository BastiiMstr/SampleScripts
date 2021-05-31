public class Main {

    public static void main(String[] args) {

        Rysownik<Kwadrat> kwadrat = new Rysownik<>(new Kwadrat());
        System.out.println(kwadrat.Co_to());
        kwadrat.rysuj(7);

        Rysownik<Prostokat> prostokat = new Rysownik<>(new Prostokat());
        System.out.println(prostokat.Co_to());
        prostokat.rysuj(4,6);

        Rysownik<Trojkat> trojkat = new Rysownik<>(new Trojkat());
        System.out.println(trojkat.Co_to());
        trojkat.rysuj(3,5);

    }
}


