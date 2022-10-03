#include <iostream>
#include <string>

class Photo 
{
    public:
        Photo(std::string s) : mTitle(s) 
        {
	        std::cout << "Processing " << mTitle << " ...\n";
        }

    private:
        std::string mTitle;
};

class PhotoProcessor
{
    protected:
        PhotoProcessor *nextProcessor;
        virtual void processMethod(Photo* ) = 0;
    public:
        PhotoProcessor () : nextProcessor(nullptr) {};
        explicit PhotoProcessor (PhotoProcessor *_nextProcessor) : nextProcessor{_nextProcessor} {};

        virtual ~PhotoProcessor(){};

        void process(Photo* _p) 
        {
            processMethod(_p);
            if (nextProcessor) 
            {
                nextProcessor -> process(_p);
            }
        }
};

class Scale : public PhotoProcessor
{
    public:
        Scale () : PhotoProcessor() {};
        explicit Scale (PhotoProcessor* _nextProcessor) : PhotoProcessor{_nextProcessor} {};
    private :
        void processMethod(Photo* _p)  override 
        {
            std::cout << "Scaling photo\n";
        }
};

class RemoveRedEye : public PhotoProcessor
{
    public:
        RemoveRedEye () : PhotoProcessor() {};
        explicit RemoveRedEye (PhotoProcessor* _nextProcessor) : PhotoProcessor{_nextProcessor} {};
    private :
        void processMethod(Photo* _p)  override 
        {
            std::cout << "Removing redeye photo\n";
        }
};

class Filter : public PhotoProcessor
{
    public:
        Filter () : PhotoProcessor() {};
        explicit Filter (PhotoProcessor* _nextProcessor) : PhotoProcessor{_nextProcessor} {};
    private :
        void processMethod(Photo* _p)  override 
        {
            std::cout << "Applying filter photo\n";
        }
};

class ColorMatch : public PhotoProcessor
{
    public:
        ColorMatch () : PhotoProcessor() {};
        explicit ColorMatch (PhotoProcessor* _nextProcessor) : PhotoProcessor{_nextProcessor} {};
    private :
        void processMethod(Photo* _p)  override 
        {
            std::cout << "Applying color match photo\n";
        }
};

void ProcessPhoto (Photo* _p) 
{
    PhotoProcessor *scale = new Scale();
    PhotoProcessor *remove = new RemoveRedEye(scale);
    PhotoProcessor *filter = new Filter(remove);
    PhotoProcessor *color = new ColorMatch(filter);

    color->process(_p);

    delete color;
    delete filter; 
    delete remove; 
    delete scale; 
}


int main () 
{
    Photo* p = new Photo("xx");
    ProcessPhoto(p);
    delete p;
    return 0;
}
