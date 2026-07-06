#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//Document ELement and its child class
class DocumentElement{
    public:
    virtual string render()=0;
};

class TextElement : public DocumentElement{
    private:
    string text;

    public:
    TextElement(string text){
        this->text=text;
    }
    string render() override{
        return text;
    }
};

class ImageElement : public DocumentElement{
    private:
    string image;

    public:
    ImageElement(string image){
        this->image=image;
    }

    string render() override{
        return "Image is "+ image+".png";
    }
};

class TabSpaceElement : public DocumentElement {
public:
    string render() override {
        return "\t";
    }
};


//DB persistence and its child class
class DbPersistence{
    public:
    virtual void save(string data)=0;
};

class saveTofile : public DbPersistence{
    public:
    void save(string data) override{
        ofstream outFile("document.txt");
        if(outFile){
            outFile<<data;
            outFile.close();
            cout<<"Documnet saved to document.txt"<<endl;

        }else{
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

class saveToDb : public DbPersistence{
    public:
    void save(string text) override{
        cout<<"Document saved to sql database"<<endl;
    }
};


//Document 
class Document {
    private:
    vector<DocumentElement*>documentElement;

    public:
    void addElement(DocumentElement* element){
        documentElement.push_back(element);
    }
    string render(){
        string result;
        for(int i=0;i<documentElement.size();i++){
            result+=documentElement[i]->render();
        }
        return result;
    }

};

class DocumentEditor {
    private:
    Document* document;
    DbPersistence* db;
    string renderedDocument;


    public:
    DocumentEditor(Document* document,DbPersistence* db){
        this->document=document;
        this->db=db;
    }

    void addText(string text){
        document->addElement(new TextElement(text));//new becaus we are creating a new object of TextElement class and passing it to the addElement function of Document class it does not delete untile we delete it explicitly
    }
    void addImage(string image){
        document->addElement(new ImageElement(image));
    }
    string renderDocument(){
        if(renderedDocument.empty()){
            renderedDocument=document->render();
        }
        return renderedDocument;
    }
    void saveDocument(){
        db->save(renderDocument());
    }
};

int main(){
    Document* document =new Document();
    DbPersistence* persistence= new saveTofile();

    DocumentEditor* editor = new DocumentEditor(document, persistence);

    editor->addText("Hello, world!");
    editor->addText("This is a real-world document editor example.");
    editor->addText("Indented text after a tab space.");
    editor->addImage("picture.jpg");

    cout<< editor->renderDocument() <<endl;
    editor->saveDocument();

    return 0;

};