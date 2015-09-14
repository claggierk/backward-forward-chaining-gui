#include <iostream>
#include <fstream>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include "BackwardChaining.h"
#include "ForwardChaining.h"
#include <pthread.h>

using std::cout;
using std::endl;
using std::cin;
using std::ofstream;

ofstream fout;

// needed for GUI
bool gQuestionAnswered = false;
bool gYES = false;

// need a handle to the XML file
GtkBuilder* userInterfaceGladeXML = NULL;

// need a handle to the actual window
GtkWidget* windowGUI = NULL;

// need windows to all of the text fields we need to modify
GtkLabel* goalText = NULL;
GtkLabel* diagnosisText = NULL;
GtkLabel* treatmentText = NULL;
GtkLabel* questionText = NULL;

// need handles to the YES and NO buttons
GtkButton* yesButton = NULL;
GtkButton* noButton = NULL;

// callback functions that will get called when the user clicks "YES" or "NO"
void ButtonPressed(GtkButton* button, gpointer user_data);
void *StartChaining(void *ptr);
void *StartGUI(void *ptr);

int main(int argc, char* argv[])
{
	::gtk_init(&argc, &argv);

	userInterfaceGladeXML = ::gtk_builder_new();
	::gtk_builder_add_from_file(userInterfaceGladeXML, "Chaining-GUI-XML.glade", NULL);

	windowGUI = GTK_WIDGET(::gtk_builder_get_object(userInterfaceGladeXML, "chainingWindow"));

	goalText = GTK_LABEL(::gtk_builder_get_object(userInterfaceGladeXML, "userRequestedGoalText"));
	diagnosisText = GTK_LABEL(::gtk_builder_get_object(userInterfaceGladeXML, "diagnosisText"));
	treatmentText = GTK_LABEL(::gtk_builder_get_object(userInterfaceGladeXML, "treatmentText"));
	questionText = GTK_LABEL(::gtk_builder_get_object(userInterfaceGladeXML, "questionBox"));
	questionText = GTK_LABEL(::gtk_builder_get_object(userInterfaceGladeXML, "questionBox"));

	yesButton = GTK_BUTTON(::gtk_builder_get_object(userInterfaceGladeXML, "yesButton"));
	::gtk_button_clicked(yesButton);
	::g_signal_connect(yesButton, "clicked", (GCallback)ButtonPressed, NULL);

	noButton = GTK_BUTTON(::gtk_builder_get_object(userInterfaceGladeXML, "noButton"));
	::gtk_button_clicked(noButton);
	::g_signal_connect(noButton, "clicked", (GCallback)ButtonPressed, NULL);

	::gtk_label_set_text(goalText, "");
	::gtk_label_set_text(diagnosisText, "");
	::gtk_label_set_text(treatmentText, "");
	::gtk_label_set_text(questionText, "");

	::gtk_widget_show(windowGUI);

	::g_object_unref( G_OBJECT(userInterfaceGladeXML));

	try
	{
		if(true)
		{
			fout.open("chaining-log.txt");
			if( !fout.is_open() )
			{
				throw string("Cannot open output file for commands.");
			}
		}

		// *************************************************************
		// ***** backward chaining ... diagnose the poison
		// *************************************************************
		pthread_t thread1;
		const char *message1 = "Thread 1";
		int iret1 = pthread_create(&thread1, NULL, StartChaining, (void*) message1);
		if(iret1)
		{
		   cout << endl << "Error - pthread_create() return code: " << iret1;
		}

		pthread_t thread2;
		const char *message2 = "Thread 2";
		int iret2 = pthread_create(&thread2, NULL, StartGUI, (void*) message2);
		if(iret2)
		{
		   cout << endl << "Error - pthread_create() return code: " << iret2;
		}

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);

		// *************************************************************
		// ***** forward chaining ... recommend treatment
		// *************************************************************
		// taken care of inside of backward chaining... as soon as all poisons have been diagnosed
	}
	catch(string message)
	{
		cout << endl << message;
	}

	cout << endl << endl << "Exiting..." << endl;
}

void *StartChaining(void *ptr)
{
	BackwardChaining* BackwardChainingInstance = new BackwardChaining("BC-Rules.txt");
	BackwardChainingInstance->run();
}

void *StartGUI(void *ptr)
{
	::gtk_main();
}

void ButtonPressed(GtkButton* button, gpointer user_data)
{
	gQuestionAnswered = true;

	if(button == yesButton && gQuestionAnswered)
	{
		gYES = true;
		cout << endl << "YES WAS PRESSED";
	}
	else if(button == noButton && gQuestionAnswered)
	{
		gYES = false;
		cout << endl << "NO WAS PRESSED";
	}
	else
	{
		cout << endl << "##### ERROR: This should never be seen ... ButtonPressed";
	}
}
