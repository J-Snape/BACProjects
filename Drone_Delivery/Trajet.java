public class Trajet
{
    private CentreDepot depotDepart;
    private CentreDepot depotDestination;

    public Trajet(CentreDepot depotDepart, CentreDepot depotDestination) {
        this.depotDepart = depotDepart;
        this.depotDestination = depotDestination;
    }

    public CentreDepot getDepotDepart() {
        return depotDepart;
    }

    public CentreDepot getDepotDestination() {
        return depotDestination;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Trajet trajet = (Trajet) o;

        if (depotDepart != null ? !depotDepart.equals(trajet.depotDepart) : trajet.depotDepart != null)
            return false;
        return depotDestination != null ? depotDestination.equals(trajet.depotDestination) : trajet.depotDestination == null;
    }

    @Override
    public int hashCode() {
        int result = depotDepart.getCodePostal().hashCode();
        result = 31 * result + depotDestination.getCodePostal().hashCode();
        return result;
    }

    @Override
    public String toString() {
        return depotDepart.getCodePostal() + " -> " + depotDestination.getCodePostal();
    }
}
