#ifndef CRAFTATTRIBUTE_H
#define CRAFTATTRIBUTE_H

#include "xmlvariablecontainer.h"
#include "xmlinteger.h"
#include "xmlboolean.h"
#include "xmlstring.h"
#include "xmlmap.h"
#include "xmlattribute.h"
#include "xmlattributeplugin.h"
#include "playerattributes.h"

class CraftProfession;

/*
 Example attribute value:

<node name="craft">
	<proficiency>
		<node name="tattooist">
			<level>3</level>
		</node>
		<node name="hairdresser">
			<level>1</level>
		</node>
	</proficiency>
	...
</node>
*/

class CraftProficiency: public XMLVariableContainer {
XML_OBJECT
public:
	typedef ::Pointer<CraftProficiency> Pointer;
	XML_VARIABLE XMLInteger level;
};

class XMLAttributeCraft: public XMLVariableContainer, 
                         public virtual EventHandler<ScoreArguments>,
                         public virtual EventHandler<WhoisArguments>
{
XML_OBJECT
public:
	typedef ::Pointer<XMLAttributeCraft> Pointer;
        typedef XMLMapBase<CraftProficiency> Proficiency;

	XMLAttributeCraft( );
	virtual ~XMLAttributeCraft( );
	
	virtual bool handle( const ScoreArguments &args ); 
	virtual bool handle( const WhoisArguments &args ); 

	int proficiencyLevel(const CraftProfession &prof) const;
	int proficiencyLevel(const DLString &profName) const;
	bool learned(const DLString &profName) const;
protected:
	XML_VARIABLE Proficiency proficiency;
};

#endif
