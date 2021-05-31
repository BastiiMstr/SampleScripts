package com.company;

import java.util.ArrayList;
import java.util.List;

public class Zegarek implements pilot,Runnable
{
    private int godzina;
    private int minuta;
    private boolean working=false;
    private List<obserwator> wyswietlacze;

    Zegarek(int godzina,int minuta)
    {
        this.godzina=godzina;
        this.minuta=minuta;

        this.wyswietlacze = new ArrayList<>();

        //Import z maina godziny i minuty oraz stworzenie listy
    }

    @Override
    public void uruchomZegar(obserwator ekran) {
        wyswietlacze.add(ekran);
    }
    //dodanie nowego wyswietlacza

    @Override
    public void wylaczZegar(obserwator ekran) {
        wyswietlacze.remove(ekran);
    }
    //usuniecie istniejacego wyswietlacza

    @Override
    public void statusZegara() {
       wyswietlacze.forEach(obserwator::update);
       //wyslanie do wszystkich podłaczonych wyświetlaczy wiadomości o zmianie
    }


    @Override
    public void run() {
        while(working)
        {
            try {
                Thread.sleep(5000);
                minuta++;
                if(minuta==60)
                {
                    minuta=0;
                    godzina++;
                }
                if(godzina==24)
                    godzina=0;

                //podliczanie godzin i minut

                statusZegara();
            }catch (InterruptedException ex){}
        }
    }

    public int getGodzina()
    {
        return godzina;
    }
    public int getMinuta()
    {
        return minuta;
    }
    public void setWorking(boolean war)
    {
        working=war;
    }
}
