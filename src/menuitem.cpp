/* This file is part of the KDE project
   Copyright 2007 Will Stephenson <wstephenson@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License or (at your option) version 3 or any later version
   accepted by the membership of KDE e.V. (or its successor approved
   by the membership of KDE e.V.), which shall act as a proxy 
   defined in Section 14 of version 3 of the license.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "menuitem.h"
#include <iostream>


MenuItem::MenuItem( bool isMenu, MenuItem * itsParent )
    : parent( itsParent ),
      menu( isMenu ),
      name( QString() ),
      caption( QString() )
    
{
    if ( parent ) {
	std::cout << "parent->children.append" << std::endl;
        parent->children.append( this );
    }
}

MenuItem::~MenuItem()
{
    qDeleteAll( children );
}

MenuItem * MenuItem::grandChildAt( int index )
{
    int count = 0;
    MenuItem * foundItem = 0;
    foreach ( MenuItem * child, children ) {
        foreach ( MenuItem * grandChild, child->children ) {
            if ( count == index ) {
                foundItem = grandChild;
                break;
            }
            count++;
        }
        if ( foundItem ) {
            break;
        }
    }
    return foundItem;
}

