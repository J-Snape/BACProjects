import java.util.ArrayList;

public class CentreDepot
{
    private String codePostal;
    private int cyclesSansDrone;
    private int nbDronesDisponibles;
    private ArrayList<Drone> listeDrones;

    public CentreDepot(String codePostal)
    {
        this.codePostal = codePostal;
        listeDrones = new ArrayList<>();
        nbDronesDisponibles = 0;
        cyclesSansDrone = 0;
    }

    public void ajouterDrone(Drone drone)
    {
        listeDrones.add(drone);
        if (!drone.estOccupe())
        {
            nbDronesDisponibles++;
            cyclesSansDrone = 0;
        }
    }

    public void enleverDrone(Drone drone)
    {
        listeDrones.remove(drone);
        nbDronesDisponibles--;
    }

    public int getNombreDronesParType(Drone.Type type)
    {
        int nbDrones = 0;

        for (Drone drone : listeDrones)
        {
            if (drone.getType() == type)
                nbDrones++;
        }
        return nbDrones;
    }

    public void incrementerCycleSansDrone()
    {
        cyclesSansDrone++;
    }

    public Drone trouverDroneDisponible(Colis colis)
    {
        for (Drone drone : listeDrones)
        {
            if ((drone.getTrajet() == null || colis.getTrajet().equals(drone.getTrajet())) &&
                    colis.getPoids() + drone.getPoids() <= drone.getPoidsMax())
                return drone;
        }

        return null;
    }

    public boolean estVide()
    {
        return nbDronesDisponibles == 0;
    }

    public String getCodePostal() {
        return codePostal;
    }

    public int getNbDronesDisponibles() {
        return nbDronesDisponibles;
    }

    public int getCyclesSansDrone() {
        return cyclesSansDrone;
    }

    @Override
    public String toString() {
        return codePostal + " cycles: " + cyclesSansDrone + " drones: " + listeDrones.size();
    }
}
