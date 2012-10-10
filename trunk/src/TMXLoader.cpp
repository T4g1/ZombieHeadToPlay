#include "TMXLoader.h"

TMXLoader::TMXLoader()
{
	// ctor
}

TMXLoader::~TMXLoader()
{
    //dtor
}

bool TMXLoader::VisitEnter (const TiXmlElement &elem, const TiXmlAttribute *attrib)
{
    if (string("map") == elem.Value()) {
        elem.Attribute("width", &m_NumMapColumns);
        elem.Attribute("height", &m_NumMapRows);

        //elem.Attribute("tileheight");
        //elem.Attribute("tilewidth");

        //TODO: get width and height, and tilewidth and tileheight
        //m_layer_width =
    }
    else if (string("tileset") == elem.Value()) {
        // Need a new class called Tileset

        elem.Attribute("tilewidth", & m_TileWidth);
        elem.Attribute("tileheight", &m_TileHeight);
        elem.Attribute("spacing", &m_TileSpacing);
        elem.Attribute("margin", &m_TilesetMargin);

        //TODO: get spacing and margin
    }
    else if (string("image") == elem.Value()) {
        //string attrib = attrib.ValueStr();
        tilesetPath = elem.Attribute("source");
    }
    else if (string("layer") == elem.Value()) {
        // We don't neet to use layer width and height yet.
        //elem.Attribute("name");
        //elem.Attribute("width");
        //elem.Attribute("height");
    }
    else if (string("data") == elem.Value()) {
        const char* text = elem.GetText();
        decode_and_store_map_data( text );
    }

    return true;
}

bool TMXLoader::loadDocument(string filename)
{
    TiXmlDocument doc(filename.c_str());

    if ( ! doc.LoadFile() ) {
		return false;
	}

    doc.Accept(this);

    return true;
}

void TMXLoader::decode_and_store_map_data( string encoded_data )
{
	vector<int> layerDataRow( getNumMapColumns() );
    int m_LayerRow = 0;
    int m_LayerCol = 0;

    vector<int> unencoded_data = base64_decode(encoded_data);

    for (int i = 0; i < getNumMapRows(); i++)
    {
        m_LayerData.push_back( layerDataRow );
    }

    for (int i = 0; i < (int)unencoded_data.size(); i += 4)
    {
        // Get the grid ID

        int a = unencoded_data[i];
        int b = unencoded_data[i + 1];
        int c = unencoded_data[i + 2];
        int d = unencoded_data[i + 3];

        int gid = a | b << 8 | c << 16 | d << 24;

        m_LayerData[m_LayerCol][m_LayerRow] = gid - 1;

        if ((i + 4) % ( getNumMapColumns() * 4) == 0) {
            m_LayerRow++;
            m_LayerCol = 0;
        }
        else {
            m_LayerCol++;
        }
    }
}