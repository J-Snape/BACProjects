import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;

/**
 * Created by chnicc on 2017-11-15.
 */
public class State {

    private HashSet<State> terminaux = new HashSet<>();
    private int noDroneCounter = 0;
    private ArrayList<Drone> listeDrone;
    private String nomEtat;
    private boolean terminal;
    private HashSet<State> nextStates;


    public State creerArbreAdresses(String nomFichier)
    {
        State nextState;
        State currentState;
        try (BufferedReader reader = new BufferedReader(new FileReader("./data/"+nomFichier+".txt")))
        {
            String line = null;
            while ((line = reader.readLine()) != null) {
                if(isValidCode(line))
                {
                    currentState = this;
                    for (int i = 1; i <= line.length(); i++) {
                        String newStateName = line.substring(0, i);
                        nextState = currentState.getNextState(newStateName);
                        if (nextState == null) {
                            if (i == line.length()) {
                                nextState = new State(newStateName, true);
                                nextState.listeDrone = new ArrayList<>();
                                this.terminaux.add(nextState);
                            } else
                                nextState = new State(newStateName, false);
                            currentState.addNextState(nextState);
                        }
                        currentState = nextState;
                    }
                }
            }
        } catch (IOException x) {
            System.err.format("IOException: %s%n", x);
        }
        return null;
    }
    public void addNextState(State state)
    {
        nextStates.add(state);
    }

    public State(String nom, boolean terminal)
    {
        this.nomEtat = nom;
        this.terminal = terminal;
        if(!terminal)
            nextStates = new HashSet<>();
    }

    public State getNextState(String c)
    {
        for (State state : nextStates)
        {
            if (state.nomEtat.equals(c))
            {
                return state;
            }
        }
        return null;
    }

    public HashSet<State> getTerminaux()
    {
        return terminaux;
    }


    public boolean verifierAddresseValide(String addresse)
    {
        for(State etat : terminaux)
            if(etat.nomEtat.equals(addresse))
                return true;

        return false;
    }

    private boolean isValidCode(String code)
    {
        boolean output = false;
        for(int i = 0; i < code.length(); i++)
        {
            if(Character.isAlphabetic(code.charAt(i)) && (i == 0 || i == 2 || i == 4))
                output = true;
            else if(Character.isDigit(code.charAt(i)) && (i == 1 || i == 3 || i == 5))
                output = true;
            else
                output = false;
        }

        return output;
    }
}
