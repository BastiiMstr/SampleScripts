package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        int GodzinaStart=15;
        int MinutaStart=0;
        boolean repeat =true;
        Zegarek zegarek = new Zegarek(GodzinaStart,MinutaStart);

        Wyswietlacz pokój = new Wyswietlacz("pokoj",zegarek);
        Wyswietlacz garaz = new Wyswietlacz("garaz",zegarek);
        Wyswietlacz kuchnia = new Wyswietlacz("kuchnia",zegarek);

        boolean pokzeg=true , kuchzeg=true , garzeg = true ,working=true;

        Thread watek = new Thread(zegarek);

        Scanner klawiatura = new Scanner(System.in);
        System.out.println("1 -> Uruchomienie/wyłaczenie głównego zegara");
        System.out.println("2 -> Uruchomienie/wyłaczenie zegara pokojowego");
        System.out.println("3 -> Uruchomienie/wyłaczenie zegara kuchennego");
        System.out.println("4 -> Uruchomienie/wyłaczenie zegara garażowego");
        System.out.println("9 -> Zamkniecie programu");
        while(repeat)
        switch(klawiatura.nextInt())
        {
            case 1:
            {
                if(working) {
                    zegarek.setWorking(true);
                    watek.start();
                    working=false;
                }else {
                    zegarek.setWorking(false);
                    working=true;
                }

                break;
            }
            case 2:
            {
                if(pokzeg) {
                    System.out.println("uruchomiono zegar pokojowy");
                    zegarek.uruchomZegar(pokój);
                    pokzeg=false;
                }
                else {
                    System.out.println("wyłaczono zegar pokojowy");
                    zegarek.wylaczZegar(pokój);
                    pokzeg=true;
                }
                break;
            }
            case 3:
            {
                if(kuchzeg) {
                    System.out.println("uruchomiono zegar kuchenny");
                    zegarek.uruchomZegar(kuchnia);
                    kuchzeg=false;

                }
                else {
                    System.out.println("wyłaczono zegar kuchenny");
                    zegarek.wylaczZegar(kuchnia);
                    kuchzeg=true;
                }
                break;
            }
            case 4:
            {
                if(garzeg) {
                    System.out.println("uruchomiono zegar garazowy");
                    zegarek.uruchomZegar(garaz);
                    garzeg=false;
                }
                else {
                    System.out.println("wyłaczono zegar garazowy");
                    zegarek.wylaczZegar(garaz);
                    garzeg=true;
                }
                break;
            }
            case 9:
            {
                repeat=false;
                break;
            }
            default:
            {
                System.out.println("nie rozpoznano komendy");
                break;
            }
        }


    }
}