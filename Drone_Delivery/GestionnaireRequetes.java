import java.io.*;
import java.util.*;

public class GestionnaireRequetes
{
    private static final int MAX_DRONES_FAIBLES = 10, MAX_DRONES_FORTS = 5;
    private ArrayList<Drone> listeDrones;
    private ArrayList<CentreDepot> listeDepots;
    private ArrayList<Colis> listeRequetes, listeRequetesReportees;
    private Etat automate;

    public GestionnaireRequetes()
    {
        //initialisation des listes
        listeDepots = new ArrayList<>();
        listeRequetes = new ArrayList<>();
        listeRequetesReportees = new ArrayList<>();

        automate = null;

        //création de drones
        listeDrones = new ArrayList<>();
        for (int i = 0; i < MAX_DRONES_FAIBLES; i++)
            listeDrones.add(new Drone(Drone.Type.FAIBLE));

        for (int i = 0; i < MAX_DRONES_FORTS; i++)
            listeDrones.add(new Drone(Drone.Type.FORT));
    }

    private void reinitialiser()
    {
        listeRequetesReportees.clear();
        listeRequetes.clear();

        for (Drone drone : listeDrones)
            drone.reinitialiser();

        listeDepots.clear();
        automate = null;
    }

    public void creerArbreAdresses(String nomFichier)
    {
        reinitialiser();

        Etat prochainEtat;
        Etat etatPresent;
        String code, nomEtat;

        try
        {
            automate = new Etat("racine", false);

            Scanner sc = new Scanner(new File("data/" + nomFichier + ".txt"));

            while(sc.hasNextLine())
            {
                code = sc.next();

                if(!code.matches("[A-Z][0-9][A-Z][0-9][A-Z][0-9]"))
                    throw new InputMismatchException();

                etatPresent = automate;

                for (int i = 1; i <= code.length(); i++)
                {
                    nomEtat = code.substring(0, i);
                    prochainEtat = etatPresent.getProchainEtat(nomEtat);
                    if (prochainEtat == null) {
                        if (i == code.length()) {
                            prochainEtat = new Etat(nomEtat, true);
                            listeDepots.add(new CentreDepot(nomEtat));
                        } else
                            prochainEtat = new Etat(nomEtat, false);
                        etatPresent.ajouterProchainEtat(prochainEtat);
                    }
                    etatPresent = prochainEtat;
                }
            }
        } catch (FileNotFoundException e)
        {
            System.out.println("Erreur! L'automate n'a pas pu être créé.");
            System.out.println("Le fichier " + nomFichier + ".txt est introuvable.\nVeuillez réessayer.");
            automate = null;
        } catch (InputMismatchException e)
        {
            System.out.println("Erreur! L'automate n'a pas pu être créé.");
            System.out.println("Au moins un code postal du fichier " + nomFichier + ".txt ne respecte pas le format " +
                    "alphanumérique A1B2C3.\nVeuillez vérifier votre fichier pour des codes illégaux.");
            automate = null;
        } catch (NoSuchElementException e)
        {
            System.out.println("Erreur! L'automate n'a pas pu être créé.");
            System.out.println("Le fichier " + nomFichier + ".txt ne respecte pas la structure demandée.\n" +
                    "Assurez-vous qu'il n'y a pas de lignes vides dans le fichier.\n" +
                    "Veuillez réessayer.");
            automate = null;
        }
    }

    public void equilibrerFlotte()
    {
        ArrayList<Colis> listeRequetesReporteesEquivalentes = new ArrayList<>();
        LinkedHashSet<Trajet> trajetsUniques = new LinkedHashSet<>();

        for (Colis colis : listeRequetesReportees)
            trajetsUniques.add(colis.getTrajet());

        if(trajetsUniques.size() != listeRequetesReportees.size())
        {
            for (Trajet trajet : trajetsUniques)
            {
                int poids = 0;
                for (Colis colis : listeRequetesReportees)
                {
                    if (trajet.equals(colis.getTrajet()))
                    {
                        poids += colis.getPoids();
                        Drone drone = trouverDroneDisponible(poids);

                        if(drone == null)
                        {
                            poids -= colis.getPoids();

                            Colis colisEquivalent = new Colis(trajet.getDepotDepart(), trajet.getDepotDestination(), poids);
                            listeRequetesReporteesEquivalentes.add(colisEquivalent);

                            poids = colis.getPoids();
                        }
                    }
                }
                listeRequetesReporteesEquivalentes.add(new Colis(trajet.getDepotDepart(), trajet.getDepotDestination(), poids));
            }
        }
        else
            listeRequetesReporteesEquivalentes = listeRequetesReportees;

        for (Colis colis : listeRequetesReporteesEquivalentes)
        {
            CentreDepot depot = colis.getDepotDepart();
            Drone drone = trouverDroneDisponible(colis.getPoids());
            if (drone != null)
                drone.tranferer(depot);
        }

        for (CentreDepot depot : listeDepots)
        {
            if(depot.estVide())
                depot.incrementerCycleSansDrone();
        }

        for (Drone drone : listeDrones)
        {
            if (droneDisponible(drone))
            {
                CentreDepot depotAbandonne = trouverDepotAbandonne();
                if(drone.getEmplacement() != depotAbandonne)
                    drone.tranferer(depotAbandonne);
            }
        }
    }

    private CentreDepot trouverDepotAbandonne()
    {
        CentreDepot depotAbandonne = null;

        if(listeDepots.size() < listeDrones.size())
        {
            int nbDronesDisponiblesMin = Integer.MAX_VALUE;
            for (CentreDepot depot : listeDepots)
            {
                if (depot.getNbDronesDisponibles() < nbDronesDisponiblesMin)
                {
                    depotAbandonne = depot;
                    nbDronesDisponiblesMin = depotAbandonne.getNbDronesDisponibles();
                }
            }
        }
        else
        {
            int nbCyclesSansDronesMax = Integer.MIN_VALUE;
            for (CentreDepot depot : listeDepots)
            {
                if (depot.getCyclesSansDrone() > nbCyclesSansDronesMax)
                {
                    depotAbandonne = depot;
                    nbCyclesSansDronesMax = depotAbandonne.getCyclesSansDrone();
                }
            }
        }
        return depotAbandonne;
    }

    private boolean droneDisponible(Drone drone)
    {
        if (drone.estOccupe())
            return false;

        for (Colis colis: listeRequetesReportees)
        {
            if (drone.getEmplacement() == colis.getDepotDepart())
                return false;
        }
        return true;
    }

    public void assignerLesColis()
    {
        for (Colis colis : listeRequetes)
        {
            CentreDepot depot = colis.getDepotDepart();
            Drone drone = depot.trouverDroneDisponible(colis);

            if (drone != null && drone.ajouterColis(colis))
                Stats.ajouterRequeteTraitee(drone.getType());
            else
                listeRequetesReportees.add(colis);
        }
    }

    public void traiterLesRequetes(String nomFichier)
    {
        listeRequetes.clear();
        listeRequetes.addAll(listeRequetesReportees);
        listeRequetesReportees.clear();

        try
        {
            Scanner sc = new Scanner(new File("data/" + nomFichier + ".txt"));
            String codeDepart, codeDestination;
            int poids;
            while(sc.hasNextLine())
            {
                codeDepart = sc.next();
                codeDestination = sc.next();
                poids = sc.nextInt();

                if (codesValides(codeDepart, codeDestination))
                    ajouterRequete(codeDepart, codeDestination, poids);
                else
                    Stats.nbRequetesInvalides++;
            }
        } catch (FileNotFoundException e)
        {
            System.out.println("Erreur!");
            System.out.println("Le fichier " + nomFichier + ".txt est introuvable.\nVeuillez réessayer.");
        } catch (NoSuchElementException e)
        {
            System.out.println("Erreur!");
            System.out.println("Le fichier " + nomFichier + ".txt ne respecte pas la structure demandée.\n" +
                    "Assurez-vous qu'il n'y a pas de lignes vides dans le fichier.\n" +
                    "Veuillez réessayer.");
        }

        assignerLesColis();

        for (Drone drone : listeDrones)
            drone.transporterColis();

        equilibrerFlotte();
    }

    private Drone trouverDroneDisponible(int poids)
    {
        for (Drone drone : listeDrones)
        {
            if (droneDisponible(drone) && poids <= drone.getPoidsMax())
                return drone;
        }
        return null;
    }

    private boolean codesValides(String codeDepart, String codeDestination)
    {
        return  automate.estCodeValide(codeDepart) && automate.estCodeValide(codeDestination)
                && !codeDepart.equals(codeDestination);
    }

    private void ajouterRequete(String codeDepart, String codeDestination, int poids)
    {
        CentreDepot depart = trouverCentreDepot(codeDepart);
        CentreDepot destination = trouverCentreDepot(codeDestination);
        listeRequetes.add(new Colis(depart, destination, poids));
    }

    private CentreDepot trouverCentreDepot(String code)
    {
        for (CentreDepot depot : listeDepots)
        {
            if (depot.getCodePostal().equals(code))
                return depot;
        }
        return null;
    }

    public Etat getAutomate() {
        return automate;
    }

    private static class Stats
    {
        public static int nbRequetesInvalides = 0;

        public static int nbRequetesTraiteesTypeFort = 0;
        public static int nbRequetesTraiteesTypeFaible = 0;

        public static void ajouterRequeteTraitee(Drone.Type type)
        {
            switch(type)
            {
                case FAIBLE:
                    nbRequetesTraiteesTypeFaible++;
                    break;
                case FORT:
                    nbRequetesTraiteesTypeFort++;
                    break;
            }
        }

        public static float getNbMoyenColisType(Drone.Type type)
        {
            float poidsMoyen = 0;

            switch(type) {
                case FAIBLE:
                    poidsMoyen = ((float) nbRequetesTraiteesTypeFaible) / MAX_DRONES_FAIBLES;
                    break;
                case FORT:
                    poidsMoyen = ((float) nbRequetesTraiteesTypeFort) / MAX_DRONES_FORTS;
                    break;
            }
            return poidsMoyen;
        }

        public static int getNbRequetesTraitees()
        {
            return nbRequetesTraiteesTypeFaible + nbRequetesTraiteesTypeFort;
        }
    }

    void afficherStatistiques()
    {
        System.out.println("STATISTIQUES : ");
        System.out.println(" ");
        System.out.println("Requetes Traitees : " + Stats.getNbRequetesTraitees());
        System.out.println("Requetes Invalides : " + Stats.nbRequetesInvalides);
        System.out.println(" ");
        System.out.println("________________________________");
        System.out.println(" ");
        System.out.println("REPARTITION DE LA FLOTTE");
        System.out.println("Quartier    |   Drones faible capacite  |   Drones forte capacite");

        for(CentreDepot depot : listeDepots)
        {
            int nbDronesFaibles = depot.getNombreDronesParType(Drone.Type.FAIBLE);
            int nbDronesForts = depot.getNombreDronesParType(Drone.Type.FORT);

            System.out.println(depot.getCodePostal().substring(0, 3) + " " + depot.getCodePostal().substring(3)
                    + " \t|\t" + nbDronesFaibles + "\t\t\t\t\t\t|\t" + nbDronesForts);
        }

        System.out.println(" ");
        System.out.println("________________________________");
        System.out.println(" ");

        System.out.println("NOMBRE MOYEN DE COLIS PAR DRONE : ");
        System.out.println("FAIBLE CAPACITÉ : " + Stats.getNbMoyenColisType(Drone.Type.FAIBLE));
        System.out.println("FORTE  CAPACITÉ : " + Stats.getNbMoyenColisType(Drone.Type.FORT));
    }
}
