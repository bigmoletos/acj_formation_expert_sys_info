// Classe de base pour les instruments
public abstract class Instrument {
    protected String name;
    protected String type;

    public Instrument(String name, String type) {
        this.name = name;
        this.type = type;
    }

    // Méthode pour jouer de l'instrument
    public abstract void play();
}

// Classe Guitare acoustique
class AcousticGuitar extends Instrument {
    public AcousticGuitar() {
        super("Guitare Acoustique", "Cordes");
    }

    @Override
    public void play() {
        System.out.println("Jouer de la guitare acoustique");
    }
}

// Classe Guitare électrique
class ElectricGuitar extends Instrument {
    public ElectricGuitar() {
        super("Guitare Électrique", "Cordes");
    }

    @Override
    public void play() {
        System.out.println("Jouer de la guitare électrique");
    }
}

// Classe Violon
class Violin extends Instrument {
    public Violin() {
        super("Violon", "Cordes");
    }

    @Override
    public void play() {
        System.out.println("Jouer du violon");
    }
}

// Classe Violoncelle
class Cello extends Instrument {
    public Cello() {
        super("Violoncelle", "Cordes");
    }

    @Override
    public void play() {
        System.out.println("Jouer du violoncelle");
    }
}

// Classe Harpe
class Harp extends Instrument {
    public Harp() {
        super("Harpe", "Cordes");
    }

    @Override
    public void play() {
        System.out.println("Jouer de la harpe");
    }
}

// Classe Trompette
class Trumpet extends Instrument {
    public Trumpet() {
        super("Trompette", "Cuivres");
    }

    @Override
    public void play() {
        System.out.println("Jouer de la trompette");
    }
}

// Classe Trombone
class Trombone extends Instrument {
    public Trombone() {
        super("Trombone", "Cuivres");
    }

    @Override
    public void play() {
        System.out.println("Jouer du trombone");
    }
}

// Classe Clarinette
class Clarinet extends Instrument {
    public Clarinet() {
        super("Clarinette", "Bois");
    }

    @Override
    public void play() {
        System.out.println("Jouer de la clarinette");
    }
}

// Classe Flûte traversière
class Flute extends Instrument {
    public Flute() {
        super("Flûte Traversière", "Bois");
    }

    @Override
    public void play() {
        System.out.println("Jouer de la flûte traversière");
    }
}

// Classe Basson
class Bassoon extends Instrument {
    public Bassoon() {
        super("Basson", "Bois");
    }

    @Override
    public void play() {
        System.out.println("Jouer du basson");
    }
}

// Classe Piano à queue
class GrandPiano extends Instrument {
    public GrandPiano() {
        super("Piano à Queue", "Claviers");
    }

    @Override
    public void play() {
        System.out.println("Jouer du piano à queue");
    }
}

// Classe Piano droit
class UprightPiano extends Instrument {
    public UprightPiano() {
        super("Piano Droit", "Claviers");
    }

    @Override
    public void play() {
        System.out.println("Jouer du piano droit");
    }
}

// Classe Xylophone
class Xylophone extends Instrument {
    public Xylophone() {
        super("Xylophone", "Percussions");
    }

    @Override
    public void play() {
        System.out.println("Jouer du xylophone");
    }
}

// Classe Marimba
class Marimba extends Instrument {
    public Marimba() {
        super("Marimba", "Percussions");
    }

    @Override
    public void play() {
        System.out.println("Jouer du marimba");
    }
}

// Classe Batterie acoustique
class AcousticDrums extends Instrument {
    public AcousticDrums() {
        super("Batterie Acoustique", "Percussions");
    }

    @Override
    public void play() {
        System.out.println("Jouer de la batterie acoustique");
    }
}

// Classe Batterie électronique
class ElectronicDrums extends Instrument {
    public ElectronicDrums() {
        super("Batterie Électronique", "Percussions");
    }

    @Override
    public void play() {
        System.out.println("Jouer de la batterie électronique");
    }
}

// Classe Synthétiseur analogique
class AnalogSynthesizer extends Instrument {
    public AnalogSynthesizer() {
        super("Synthétiseur Analogique", "Électroniques");
    }

    @Override
    public void play() {
        System.out.println("Jouer du synthétiseur analogique");
    }
}

// Classe Clavier MIDI
class MIDIDrum extends Instrument {
    public MIDIDrum() {
        super("Clavier MIDI", "Électroniques");
    }

    @Override
    public void play() {
        System.out.println("Utiliser le clavier MIDI");
    }
}
