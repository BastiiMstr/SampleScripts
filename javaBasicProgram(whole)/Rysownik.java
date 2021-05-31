public class Rysownik <T extends inter>{
    T klasa;
    public String Co_to ()
    {
        return klasa.typ();
    }
    public Rysownik(T klasa)
    {
        this.klasa = klasa;
    }
    public void rysuj(double a)
    {
        klasa.draw(a);
    }

    public void rysuj(double a, double b) {
        klasa.draw(a,b);
    }
}
