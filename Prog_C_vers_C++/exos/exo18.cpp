using Persona = map<string, vector<string>>;

Persona clone_persona(const Persona p) { /* pat valeur */ }
void print_persona(const Persona &p) { /* code */ }
void adjust_persona(Persona &p) { /* code */ }
vector<Persona> init_personas(const string f_name) { /* e const ici ne sert à rien  */ } // lcar f-name est par valeur

int main(int argc, char **argv)
{
    const string path_name("../configs/all_default_personas.txt");
    constexpr string filename(toupper(path_name));
    {
        vector<Persona> all_people = init_personas(filename);
        Persona P;

        for (Persona p : all_people)
        {
            P = clone_persona(p);
            adjust_persona(P);
            show_persona(P);
        }
    }

    /* code of the gameplay */
}
