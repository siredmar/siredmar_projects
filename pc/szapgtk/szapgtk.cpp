#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>

using namespace std;

static GtkWidget *entry;
static char *channel;
void change_channel();



void channel_up()
{

    int x;
    //sscanf(channel,"%d",x);

    x = atoi(channel);
    x = x + 1;			//073746353;
    cout << x << endl;


    sprintf(channel, "%d", x);


    cout << channel << endl << x << endl;
    gtk_entry_set_text(GTK_ENTRY(entry), channel);

    change_channel();

}

void channel_down()
{



    int x;
    //sscanf(channel,"%d",x);
    x = atoi(channel);
    x = x - 1;
    cout << x << endl;


    sprintf(channel, "%d", x);


    cout << channel << endl << x << endl;
    gtk_entry_set_text(GTK_ENTRY(entry), channel);

    change_channel();



}


void change_channel()
{

    char *channel;
    channel = gtk_entry_get_text(GTK_ENTRY(entry));
    if (channel != (char *) NULL)


	cout << "Channel: " << channel << endl;
    system("killall -9 szap");

    pid_t child;

    child = fork();
    if (!child) {

	execl("/usr/bin/szap", "szap", "-n", channel, NULL);

    } else if (child > 0) {


    } else
	perror("fork");

}

void kill_szap()
{
    system("killall -9 szap");
    //gtk_main_quit();
}

void quit_program()
{
    system("killall -9 szap");
    gtk_main_quit();
}


int main(int argc, char *argv[])
{

    GtkWidget *window, *button_ok, *button_kill, *button_exit,
	*button_channel_up, *button_channel_down, *table;



    gtk_set_locale();

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_policy(GTK_WINDOW(window), FALSE, FALSE, FALSE);

    gtk_signal_connect(GTK_OBJECT(window), "destroy",
		       GTK_SIGNAL_FUNC(quit_program), NULL);

    gtk_window_set_title(GTK_WINDOW(window), "szap gtk");
    gtk_container_border_width(GTK_CONTAINER(window), 5);

    table = gtk_table_new(3, 4, FALSE);
    button_exit = gtk_button_new_with_label("Exit");
    gtk_widget_set_usize(button_exit, 60, 22);

    button_kill = gtk_button_new_with_label("Kill");
    gtk_widget_set_usize(button_exit, 60, 22);

    button_ok = gtk_button_new_with_label("OK");
    gtk_widget_set_usize(button_ok, 60, 22);

    button_channel_up = gtk_button_new_with_label("AUF");
    gtk_widget_set_usize(button_channel_up, 60, 22);

    button_channel_down = gtk_button_new_with_label("AB");
    gtk_widget_set_usize(button_channel_down, 60, 22);

    entry = gtk_entry_new();
    gtk_widget_set_usize(entry, 102, 22);
    gtk_editable_select_region(GTK_EDITABLE(entry), 0, -1);
    gtk_entry_set_text(GTK_ENTRY(entry), "1");



    gtk_table_attach_defaults(GTK_TABLE(table), entry, 0, 1, 0, 1);
    gtk_widget_show(entry);

    gtk_table_attach_defaults(GTK_TABLE(table), button_ok, 1, 2, 1, 2);
    gtk_widget_show(button_ok);

    gtk_table_attach_defaults(GTK_TABLE(table), button_kill, 1, 2, 2, 3);
    gtk_widget_show(button_kill);

    gtk_table_attach_defaults(GTK_TABLE(table), button_exit, 1, 2, 3, 4);
    gtk_widget_show(button_exit);

    gtk_table_attach_defaults(GTK_TABLE(table), button_channel_up, 0, 1, 1,
			      2);
    gtk_widget_show(button_channel_up);

    gtk_table_attach_defaults(GTK_TABLE(table), button_channel_down, 0, 1,
			      2, 3);
    gtk_widget_show(button_channel_down);

    gtk_signal_connect_object(GTK_OBJECT(button_ok), "clicked",
			      GTK_SIGNAL_FUNC(change_channel),
			      GTK_OBJECT(window));

    gtk_signal_connect_object(GTK_OBJECT(button_exit), "clicked",
			      GTK_SIGNAL_FUNC(quit_program),
			      GTK_OBJECT(window));

    gtk_signal_connect_object(GTK_OBJECT(button_kill), "clicked",
			      GTK_SIGNAL_FUNC(kill_szap),
			      GTK_OBJECT(window));

    gtk_signal_connect_object(GTK_OBJECT(button_channel_up), "clicked",
			      GTK_SIGNAL_FUNC(channel_up),
			      GTK_OBJECT(window));

    gtk_signal_connect_object(GTK_OBJECT(button_channel_down), "clicked",
			      GTK_SIGNAL_FUNC(channel_down),
			      GTK_OBJECT(window));


    gtk_container_add(GTK_CONTAINER(window), table);
    channel = gtk_entry_get_text(GTK_ENTRY(entry));



    pid_t child;

    child = fork();
    if (!child) {

	execl("/usr/bin/szap", "szap", "-n", "001", NULL);

    } else if (child > 0) {


    } else
	perror("fork");


    cout << channel << endl;


    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
