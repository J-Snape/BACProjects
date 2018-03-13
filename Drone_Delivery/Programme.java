import javax.swing.*;
import java.io.IOException;
import java.util.Scanner;

public class Programme {
    private GestionnaireRequetes gestionnaireRequetes;

    public Programme()
    {
        gestionnaireRequetes = new GestionnaireRequetes();
        afficherMenuPrincipal();
    }

    public void effectuerOperation(String entree)
    {
        switch (entree) {
            case "a":
                creerAutomate();
                break;
            case "b":
                traiterRequete();
                break;
            case "c":
                afficherStatistiques();
                break;
            default:
                System.out.println("Entrée invalide.\nVeuillez réesayer.");
        }
    }

    public void afficherMenuPrincipal()
    {
        System.out.println("");
        System.out.println( "  **************************************" );
        System.out.println( "  **************************************" );
        System.out.println( "  ***                                ***" );
        System.out.println( "  ***    LOG2810 TP2 - Main Menu     ***" );
        System.out.println( "  ***                                ***" );
        System.out.println( "  ***            Code par:           ***" );
        System.out.println( "  ***       Christopher Nicolae      ***" );
        System.out.println( "  ***           Jared Snape          ***" );
        System.out.println( "  ***     Guy-Frank Essome Penda     ***" );
        System.out.println( "  ***                                ***" );
        System.out.println( "  **************************************" );
        System.out.println( "  **************************************" );
        System.out.println("");
        System.out.println( "               (a) Creer l'automate" );
        System.out.println( "               (b) Traiter Requete" );
        System.out.println( "               (c) Afficher Statistiques" );
        System.out.println( "               (d) Quitter" );
    }

    private void creerAutomate()
    {
        System.out.println("Entrez votre nom de fichier (sans extension)");
        Scanner sc = new Scanner(System.in);
        String nomFichier = sc.nextLine();

        gestionnaireRequetes.creerArbreAdresses(nomFichier);

        if(gestionnaireRequetes.getAutomate() != null)
        {
            gestionnaireRequetes.equilibrerFlotte();
            System.out.println("Automate créé avec succès!");
        }
    }

    private void traiterRequete()
    {
        if(gestionnaireRequetes.getAutomate() != null)
        {
            System.out.println("Entrez votre nom de fichier (sans extension)");
            Scanner sc = new Scanner(System.in);
            String nomFichier = sc.nextLine();

            gestionnaireRequetes.traiterLesRequetes(nomFichier);
            System.out.println("Le traitement des requêtes est terminé!");
        }
        else
            System.out.println("Veuillez créer l'automate avant de traiter des requetes (option a)");
    }

    private boolean afficherStatistiques()
    {
        if(gestionnaireRequetes.getAutomate() != null)
        {

            gestionnaireRequetes.afficherStatistiques();

            System.out.println("appuyez sur ENTER pour continuer...");
            Scanner sc = new Scanner(System.in);
            sc.nextLine();
        }
        else
            System.out.println("Veuillez créer l'automate avant de traiter des requetes (option a)");
        return false;
    }
}
