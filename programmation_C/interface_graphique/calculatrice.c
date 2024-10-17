#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <cstdlib>
#include <cstring>
#include <string>
#include <deque>

Fl_Input *display;  // Zone d'affichage de la calculatrice
Fl_Text_Display *history_display;  // Zone d'affichage de l'historique
Fl_Text_Buffer *history_buffer;  // Buffer pour l'historique des lignes
std::deque<std::string> history;  // Stockage des 10 dernières lignes
char operation = 0; // Opération en cours
double first_operand = 0;  // Premier opérande

// Fonction de gestion des clics sur les boutons des chiffres
void number_cb(Fl_Widget *widget, void *) {
    const char *label = widget->label();  // Récupère le label du bouton cliqué
    display->insert(label);  // Insère le label dans le champ d'affichage
}

// Fonction pour les opérations (+, -, *, /)
void operation_cb(Fl_Widget *widget, void *) {
    const char *label = widget->label();
    first_operand = atof(display->value());  // Convertit l'affichage en nombre
    operation = label[0];  // Récupère le type d'opération
    display->value("");  // Vide l'affichage pour le deuxième nombre
}

// Fonction pour le calcul du résultat
void equal_cb(Fl_Widget *widget, void *) {
    double second_operand = atof(display->value());  // Récupère le deuxième opérande
    double result = 0;

    switch (operation) {
        case '+':
            result = first_operand + second_operand;
            break;
        case '-':
            result = first_operand - second_operand;
            break;
        case '*':
            result = first_operand * second_operand;
            break;
        case '/':
            if (second_operand != 0)
                result = first_operand / second_operand;
            else
                result = 0;  // Gestion de la division par 0
            break;
        default:
            break;
    }

    // Ajouter l'opération et le résultat à l'historique
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "%g %c %g = %g", first_operand, operation, second_operand, result);
    std::string operation_result = buffer;

    // Stocker la ligne dans l'historique (garder seulement les 10 dernières)
    if (history.size() == 10) {
        history.pop_front();  // Retirer l'entrée la plus ancienne
    }
    history.push_back(operation_result);  // Ajouter la nouvelle entrée

    // Mettre à jour l'affichage de l'historique
    std::string full_history;
    for (const auto &line : history) {
        full_history += line + "\n";  // Ajouter un retour à la ligne après chaque entrée
    }
    history_buffer->text(full_history.c_str());

    // Afficher le résultat
    snprintf(buffer, sizeof(buffer), "%g", result);  // Convertir le résultat en chaîne
    display->value(buffer);  // Afficher le résultat
}

// Fonction pour effacer l'affichage
void clear_cb(Fl_Widget *widget, void *) {
    display->value("");  // Vide le champ d'affichage
    operation = 0;
    first_operand = 0;
}

int main() {
    Fl_Window *window = new Fl_Window(300, 500, "Calculatrice");

    // Zone d'affichage principale
    display = new Fl_Input(10, 10, 280, 40);
    display->readonly(1);
    display->textsize(24);

    // Affichage de l'historique
    history_buffer = new Fl_Text_Buffer();
    history_display = new Fl_Text_Display(10, 60, 280, 100);
    history_display->buffer(history_buffer);

    // Couleurs pour les boutons
    Fl_Color number_color = FL_GREEN;
    Fl_Color operator_color = FL_YELLOW;
    Fl_Color equal_color = FL_RED;

    // Boutons des chiffres
    const int btn_width = 70;
    const int btn_height = 50;

    Fl_Button *btn_1 = new Fl_Button(10, 180, btn_width, btn_height, "1");
    btn_1->color(number_color);
    btn_1->callback(number_cb);

    Fl_Button *btn_2 = new Fl_Button(90, 180, btn_width, btn_height, "2");
    btn_2->color(number_color);
    btn_2->callback(number_cb);

    Fl_Button *btn_3 = new Fl_Button(170, 180, btn_width, btn_height, "3");
    btn_3->color(number_color);
    btn_3->callback(number_cb);

    Fl_Button *btn_4 = new Fl_Button(10, 240, btn_width, btn_height, "4");
    btn_4->color(number_color);
    btn_4->callback(number_cb);

    Fl_Button *btn_5 = new Fl_Button(90, 240, btn_width, btn_height, "5");
    btn_5->color(number_color);
    btn_5->callback(number_cb);

    Fl_Button *btn_6 = new Fl_Button(170, 240, btn_width, btn_height, "6");
    btn_6->color(number_color);
    btn_6->callback(number_cb);

    Fl_Button *btn_7 = new Fl_Button(10, 300, btn_width, btn_height, "7");
    btn_7->color(number_color);
    btn_7->callback(number_cb);

    Fl_Button *btn_8 = new Fl_Button(90, 300, btn_width, btn_height, "8");
    btn_8->color(number_color);
    btn_8->callback(number_cb);

    Fl_Button *btn_9 = new Fl_Button(170, 300, btn_width, btn_height, "9");
    btn_9->color(number_color);
    btn_9->callback(number_cb);

    Fl_Button *btn_0 = new Fl_Button(90, 360, btn_width, btn_height, "0");
    btn_0->color(number_color);
    btn_0->callback(number_cb);

    // Boutons des opérations
    Fl_Button *btn_add = new Fl_Button(250, 180, 40, btn_height, "+");
    btn_add->color(operator_color);
    btn_add->callback(operation_cb);

    Fl_Button *btn_sub = new Fl_Button(250, 240, 40, btn_height, "-");
    btn_sub->color(operator_color);
    btn_sub->callback(operation_cb);

    Fl_Button *btn_mul = new Fl_Button(250, 300, 40, btn_height, "*");
    btn_mul->color(operator_color);
    btn_mul->callback(operation_cb);

    Fl_Button *btn_div = new Fl_Button(250, 360, 40, btn_height, "/");
    btn_div->color(operator_color);
    btn_div->callback(operation_cb);

    // Bouton égal
    Fl_Button *btn_equal = new Fl_Button(170, 360, btn_width, btn_height, "=");
    btn_equal->color(equal_color);
    btn_equal->callback(equal_cb);

    // Bouton de réinitialisation
    Fl_Button *btn_clear = new Fl_Button(10, 360, btn_width, btn_height, "C");
    btn_clear->color(FL_CYAN);
    btn_clear->callback(clear_cb);

    // Afficher la fenêtre et les widgets
    window->end();
    window->show();

    return Fl::run();
}
