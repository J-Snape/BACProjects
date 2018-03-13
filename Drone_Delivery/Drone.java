import java.util.ArrayList;

/**
 * Created by chnicc on 2017-11-22.
 */
public class Drone
{

    public enum Type
    {
        FAIBLE, FORT
    }

    public static final int MAX_POIDS_FAIBLE = 1000;
    public static final int MAX_POIDS_FORT = 5000;

    private CentreDepot emplacement;
    private Trajet trajet;
    private ArrayList<Colis> listeColis;
    private int poids;
    private Type type;

    public Drone(Type type) {
        emplacement = null;
        trajet = null;
        listeColis = new ArrayList<>();

        this.type = type;
        poids = 0;
    }

    public void reinitialiser()
    {
        listeColis.clear();
        emplacement = null;
        trajet = null;
        poids = 0;
    }

    public void tranferer(CentreDepot destination)
    {
        if (emplacement != null)
        {
            emplacement.enleverDrone(this);
            emplacement = null;
        }
        destination.ajouterDrone(this);
        emplacement = destination;
        trajet = null;
    }

    public void transporterColis()
    {
        if(!listeColis.isEmpty())
        {
            Colis colis = listeColis.get(0);
            CentreDepot depart = colis.getDepotDepart();
            CentreDepot destination = colis.getDepotDestination();

            poids -= colis.getPoids();
            listeColis.remove(colis);

            if(emplacement != destination)
            {
                depart.enleverDrone(this);
                destination.ajouterDrone(this);
                emplacement = destination;
            }
        }
    }

    public boolean ajouterColis(Colis colis)
    {
        if (poids + colis.getPoids() <= getPoidsMax())
        {
            listeColis.add(colis);
            poids += colis.getPoids();
            trajet = colis.getTrajet();
            return true;
        }
        return false;
    }

    public boolean estOccupe()
    {
        return listeColis.size() != 0;
    }

    public Type getType() {
        return type;
    }

    public int getPoids() {
        return poids;
    }

    public int getPoidsMax()
    {
        if (type == Type.FAIBLE)
            return MAX_POIDS_FAIBLE;
        else
            return MAX_POIDS_FORT;
    }

    public CentreDepot getEmplacement() {
        return emplacement;
    }

    public Trajet getTrajet() {
        return trajet;
    }

    @Override
    public String toString() {
        if(emplacement != null)
            return "centre: " + emplacement.getCodePostal() + " " + type + " colis: " + listeColis.size() + " poids: " + poids;
        return type + " colis: " + listeColis.size();
    }
}
