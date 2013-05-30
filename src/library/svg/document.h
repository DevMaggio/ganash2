#ifndef GANASH_SVG_DOCUMENT_H
#define GANASH_SVG_DOCUMENT_H

namespace Ganash {
namespace Svg {

#include "dom/document.h"

//class DOMImplementation;
//class SVGElement;
//class SVGSVGElement;

class Document : public Ganash::Dom::Document
{
public:
    //static PassRefPtr<Document> create(Frame* frame, const KURL& url)
    //{
    //    return adoptRef(new SVGDocument(frame, url));
    //}
    //SVGSVGElement* rootElement() const;
protected:
    Document();

};

} // namespace Svg
} // namespace Ganash

#endif // GANASH_SVG_DOCUMENT_H
