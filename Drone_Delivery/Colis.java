/**
 * Created by chnicc on 2017-11-22.
 */
public class Colis {

    private Trajet trajet;
    private int poids;

    public Colis(CentreDepot depart, CentreDepot destination, int poids)
    {
        trajet = new Trajet(depart, destination);
        this.poids = poids;
    }

    public int getPoids() {
        return poids;
    }

    public Trajet getTrajet() {
        return trajet;
    }

    public CentreDepot getDepotDepart() {
        return trajet.getDepotDepart();
    }

    public CentreDepot getDepotDestination() {
        return trajet.getDepotDestination();
    }



    @Override
    public String toString() {
        return trajet.toString() + " poids: " + poids;
    }
}
