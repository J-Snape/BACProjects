import java.util.Scanner;

import static java.lang.Thread.sleep;

public class Main
{
    //Debut fonction main
    public static void main(String[] args) {

       Programme programme = new Programme();

        System.out.print("Entrez votre choix (une lettre): ");
        Scanner sc = new Scanner(System.in);
        String entree = sc.next();

        while (!entree.equalsIgnoreCase("d"))
        {
            try
            {
                programme.effectuerOperation(entree.toLowerCase());
                sleep(2000);
            } catch (InterruptedException e){
                throw new Error(e);
            }

            programme.afficherMenuPrincipal();

            System.out.print("Entrez votre choix (une lettre): ");
            entree = sc.next();
        }

        System.out.println("Merci d'utiliser notre programme!\nAu revoir!!!");
    }
}


