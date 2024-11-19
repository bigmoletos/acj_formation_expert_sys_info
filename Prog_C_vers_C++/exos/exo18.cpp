using Persona = map<string, vector<string>>;

Persona clone_persona(const Persona p) { /* pat valeur */ }
void print_persona(const Persona &p) { /* code */ }
void adjust_persona(Persona &p) { /* code */ }
vector<Persona> init_personas(const string f_name) { /* e const ici ne sert Ã  rien  */ } // lcar f-name est par valeur

/**
 * @brief [Description de main]
 *
 * @param argc [Description du paramètre]
 * @param **argv [Description du paramètre]
 * @return int [Description du retour]
 */
int main(int argc, char **argv)
{
/**
 * @brief [Description de path_name]
 *
 * @param "../configs/all_default_personas.txt" [Description du paramètre]
 * @return const string [Description du retour]
 */
    const string path_name("../configs/all_default_personas.txt");
/**
 * @brief [Description de filename]
 *
 * @param toupper(path_name) [Description du paramètre]
 * @return constexpr string [Description du retour]
 */
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
