#ifndef TMXLOADER_H
#define TMXLOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "base64.h"
#include "tinyxml/tinyxml.h"

using namespace std;


class TMXLoader :
	public TiXmlVisitor
{
    public:
        TMXLoader();
        virtual ~TMXLoader();

		// Callback de TinyXML
		//TODO: for performance, we may not want to return true for each of
		// these callbacks for the visitor pattern.
		virtual bool VisitEnter  (const TiXmlDocument  &) { return true; }
        virtual bool VisitExit (const TiXmlDocument &) { return true; }
        virtual bool VisitExit (const TiXmlElement &) { return true; }
		virtual bool Visit (const TiXmlDeclaration &) { return true; }
        virtual bool Visit (const TiXmlText &) { return true; }
        virtual bool Visit (const TiXmlComment &) { return true; }
        virtual bool Visit (const TiXmlUnknown &) { return true; }
		
        virtual bool VisitEnter (const TiXmlElement &, const TiXmlAttribute *);

		// Demande le chargement d'un fichier précis
        bool loadDocument(string filename);

		// Accesseurs
        int getTileWidth() const { return m_TileWidth; }
        int getTileHeight() const { return m_TileWidth; }
        int getTileSpacing() const { return m_TileSpacing; }
        int getTilesetMargin() const { return m_TilesetMargin; }
        int getNumMapColumns() const { return m_NumMapColumns; }
        int getNumMapRows() const { return m_NumMapRows; }
		string getTilesetPath() const { return tilesetPath; }
		vector<vector<int>> getLayerData() const { return m_LayerData; }
    protected:
    private:
        int m_TileWidth;
        int m_TileHeight;
        int m_TileSpacing;
        int m_TilesetMargin;
        int m_NumMapColumns;
        int m_NumMapRows;
		string tilesetPath;

        vector<vector<int>> m_LayerData;

        void decode_and_store_map_data( string encoded_data );
};

#endif // TMXLOADER_H