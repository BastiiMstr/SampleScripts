package com.company;

public class Wyswietlacz implements obserwator
{
    private String wiadomosc ="Wyświetlacz %s: %d:%d";
    private String nazwa;
    private Zegarek obserwowany;

    Wyswietlacz(String nazwa, Zegarek zegarek)
    {
        this.nazwa=nazwa;
        obserwowany=zegarek;
    }
    @Override
    public void update() {
        System.out.println(String.format(wiadomosc,nazwa,obserwowany.getGodzina(),obserwowany.getMinuta()));
        //Wyświetlenie zmiennej wiadomosc nazwa oraz zaimportowanie z zegarka aktualnej godziny i minuty
    }

}
