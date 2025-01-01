#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QComboBox>
#include "convertxmltojson.h"
#include "minifying.h"
#include "PrettifyXml.h"
#include "compHeader.h"
#include "ErrorHandling.h"
#include "network_analysis.h"
#include "SearchByWordTopic.h"
#include "XML_to_graph.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_COPY_BUTTON_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_CLOSE_COPY_LABEL_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_BROWSE_BUTTON_clicked()
{
    // Open file dialog to select a file
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", tr("All files (*.*)"));

    // Check if a file was selected (filename is not empty)
    if (!filename.isEmpty()) {
        // Display the selected file's name in a message box
        QMessageBox::information(this, tr("File Name"), filename);

        // Create a new file called input.xml
        QString outputFile = "input.xml";
        QFile file(outputFile);

        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            // File opened successfully, now write the content of the selected file into input.xml
            QFile selectedFile(filename);

            if (selectedFile.open(QIODevice::ReadOnly)) {
                QByteArray content = selectedFile.readAll();  // Read all data from the selected file

                // Write the content to input.xml
                file.write(content);
                selectedFile.close();

                QMessageBox::information(this, tr("File Created"), tr("input.xml has been created successfully!"));
            } else {
                // If the selected file couldn't be opened, show an error
                QMessageBox::critical(this, tr("Error"), tr("Failed to open the selected file."));
            }

            file.close();  // Close input.xml after writing
        } else {
            // If input.xml couldn't be created, show an error
            QMessageBox::critical(this, tr("Error"), tr("Failed to create input.xml."));
        }

        // Switch to the second page of the stacked widget (index 2)
        ui->stackedWidget->setCurrentIndex(2);
    } else {
        // If no file is selected, show an error message
        QMessageBox::warning(this, tr("No File Selected"), tr("Please select a file."));
    }
}


void MainWindow::on_BACK_BROWSE_BUTTON_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}




void MainWindow::on_OK_COPY_BUTTON_clicked()
{
    QString s = ui->XML_TEXT->toPlainText();

    QFile file("input.xml"); // create an input file

    // // Open the file in write-only mode
    // if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
    //     QTextStream out(&file);
    //     out << s;
    //     file.close();
    //     qDebug() << "File written successfully.";
    // } else{
    //     qDebug() << "Error: Unable to open file for writing.";
    // }


    //////////////////////////////////////////////////////////
    // Open the file in write-only mode to truncate its content
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << file.errorString();
        // return;
    }

    QTextStream out(&file);
    out << s;  // Write the provided content to the file
    file.close();        // Close the file
    qDebug() << "File written successfully.";
    //////////////////////////////////////////////////////////

     ui->stackedWidget->setCurrentIndex(2);


}


void MainWindow::on_Most_follower_button_clicked()
{

}


void MainWindow::on_most_active_clicked()
{

    vector<pair<string, int>> most_Active = MostActive(xmlToGraph("input.xml"));

    // Convert vector content to a QString
    QString output;
    for (const auto& follower : most_Active) {
        output += "Name: " + QString::fromStdString(follower.first) +endl+ "ID: " + QString::number(follower.second);
    }

    // Display in a QMessageBox
    QMessageBox::information(this, "Most Active", output);
}

#include <QInputDialog>

void MainWindow::on_mutual_followers_clicked()
{
    // Get user input for IDs as a comma-separated string
    bool ok;
    QString text = QInputDialog::getText(this, "Input IDs", "Enter IDs (comma-separated):", QLineEdit::Normal, "", &ok);


    if (ok && !text.isEmpty()) {
        // Split the input into a vector of strings
        vector<string> v;
        for (const QString& id : text.split(',')) {
            v.push_back(id.trimmed().toStdString()); // Remove spaces and convert to std::string
        }

        // Call the method
        vector<pair<string, int>> mutual_followers = MutualUsers(xmlToGraph("input.xml"), v);

        // Convert vector content to a QString for display


        QString output;
        if (mutual_followers.empty()) {
            // If no mutual followers, set a custom message
            output = "There are no mutual followers.";
        } else {
            // If there are mutual followers, construct the output string
            for (const auto& follower : mutual_followers) {
                output += "Name: " + QString::fromStdString(follower.first) + "\nID: " + QString::number(follower.second) + "\n\n";
            }
        }

        // Display the result in a QMessageBox
        QMessageBox::information(this, "Mutual Followers", output);
    }
}


void MainWindow::on_suggestions_clicked()
{
    // Prompt the user for the ID input
    bool ok;
    QString userID = QInputDialog::getText(this, "Enter User ID", "Enter the user ID for suggestions:", QLineEdit::Normal, "", &ok);

    if (ok && !userID.isEmpty()) {
        // Convert the user ID to std::string
        string idd = userID.toStdString();

        // Call the SuggestFollowers function with the user ID
        vector<pair<string, int>> suggestion_followers = SuggestFollowers(xmlToGraph("input.xml"), idd);

        QString output;
        if (suggestion_followers.empty()) {
            // If no suggestions, show a custom message
            output = "No suggestions available.";
        } else {
            // Construct the output string with suggested users
            for (const auto& follower : suggestion_followers) {
                output += "Suggested user: " + QString::fromStdString(follower.first) + "\nID: " + QString::number(follower.second) + "\n\n";
            }
        }

        // Display the suggestions in a QMessageBox
        QMessageBox::information(this, "Suggested Followers", output);
    } else {
        // Handle the case where the user canceled the input
        QMessageBox::warning(this, "Input Canceled", "You canceled or entered an empty input.");
    }
}


void MainWindow::on_dropdown_currentTextChanged(const QString &arg1)
{
    if (ui->dropdown->currentText() == "Network Analysis") {
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if(ui->dropdown->currentText() == "to JSON"){

        ifstream file("input.xml");
        ofstream temp("inputtoJSON.xml");
        PrettifyXML(ReadXml(file),temp);

        ifstream inputtoJSON("inputtoJSON.xml");
        ofstream outputFile("outputJSON.json");
        convertXMLtoJSON(inputtoJSON,outputFile);

    }
    else if(ui->dropdown->currentText() == "Check Consistency"){

        ifstream file("input.xml");
        ofstream outputfile("outputerrorHandling.xml");
        error_handling(file,outputfile);

    }
    else if(ui->dropdown->currentText() == "Minifying"){
         minifying("input.xml","outputminifying.xml");

    }
    else if(ui->dropdown->currentText() == "Prettifying"){
        ifstream file("input.xml");
        ofstream outputFile("outputPrettify.xml");
        PrettifyXML(ReadXml(file),outputFile);
    }
    else if(ui->dropdown->currentText() == "Compress"){
        // ifstream file("input.xml");
        compress("input.xml","output.comp");

    }
    else if(ui->dropdown->currentText() == "Decompress"){
        decompress("output.comp","decomp.xml");

    }
    else if(ui->dropdown->currentText() == "Graph Visualization"){

        xmlToGraph_abdo("input.xml", "output.dot");
        visualizeGraph("output.dot", "outputgraphviz.jpg");

    }

    else if(ui->dropdown->currentText() == "Network Analysis"){
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if(ui->dropdown->currentText() == "Search"){
        ui->stackedWidget->setCurrentIndex(4);
    }

    else if(ui->dropdown->currentText() == "Choose the feature"){
        ///

    }

}


void MainWindow::on_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_back_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_most_follower_clicked()
{
    vector<pair<string, int>> mostFollower = MostInfluencer(xmlToGraph("input.xml"));

    // Convert vector content to a QString
    QString output;
    for (const auto& follower : mostFollower) {
        output += "Name: " + QString::fromStdString(follower.first) +endl+ "ID: " + QString::number(follower.second);
    }

    // Display in a QMessageBox
    QMessageBox::information(this, "Most Followers", output);
}





void MainWindow::on_Search_Back_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_SearchByTopic_clicked()
{
    // Retrieve the text from textEdit_2
    QString text = ui->textEdit_2->toPlainText();

    // Convert the text to std::string (if needed)
    std::string textStr = text.toStdString();
    // textStr=textStr.tolower();

    // Call SearchByTopic with the input text
    ifstream file("input.xml");
    vector<pair<int, string>> searched_by_topic = SearchByTopic(ReadXmlToTree(file), textStr);

    // Prepare the output string to display in the pop-up
    QString output;
    if (searched_by_topic.empty()) {
        output = "No results found for the topic.";
    } else {
        for (const auto& item : searched_by_topic) {
            output += "ID: " + QString::number(item.first) + "\nTopic: " + QString::fromStdString(item.second) + "\n\n";
        }
    }

    // Display the results in a QMessageBox
    QMessageBox::information(this, "Search Results", output);
}




void MainWindow::on_SearchBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_SearchByWord_clicked()
{
    // Retrieve the text from textEdit_2
    QString text = ui->textEdit_2->toPlainText();

    // Convert the text to std::string (if needed)
    std::string textStr = text.toStdString();

    // Convert the search term to lowercase for case-insensitive search
    std::transform(textStr.begin(), textStr.end(), textStr.begin(), ::tolower);

    // Call SearchByWord with the input text
    ifstream file("input.xml");
    vector<pair<int, string>> searched_by_word = SearchByWord(ReadXmlToTree(file), textStr);

    // Prepare the output string to display in the pop-up
    QString output;
    if (searched_by_word.empty()) {
        output = "No results found for the word.";
    } else {
        for (const auto& item : searched_by_word) {
            output += "ID: " + QString::number(item.first) + "\nPost: " + QString::fromStdString(item.second) + "\n\n";
        }
    }

    // Display the results in a QMessageBox
    QMessageBox::information(this, "Search Results", output);
}


