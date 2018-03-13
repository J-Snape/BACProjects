import java.util.HashSet;

/**
 * Created by chnicc on 2017-11-15.
 */
public class Etat {

    private String nom;
    private boolean terminal;
    private HashSet<Etat> prochainsEtats;

    public Etat(String nom, boolean terminal)
    {
        this.nom = nom;
        this.terminal = terminal;
        if(!terminal)
            prochainsEtats = new HashSet<>();
    }

    public void ajouterProchainEtat(Etat etat)
    {
        prochainsEtats.add(etat);
    }

    public Etat getProchainEtat(String nom)
    {
        for (Etat etat : prochainsEtats)
        {
            if (etat.nom.equals(nom))
                return etat;
        }
        return null;
    }

    public boolean estCodeValide(String code)
    {
        Etat etat = this;
        for (int i = 1; i <= code.length() && etat != null; i++)
            etat = etat.getProchainEtat(code.substring(0, i));

        if(etat != null && etat.terminal)
            return true;
        else
            return false;
    }
}
