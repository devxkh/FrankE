//Copyright (c) 2011 Oscar (.teri) Triano <teritriano@gmail.com>

//This software is provided 'as-is', without any express or implied
//warranty. In no event will the authors be held liable for any damages
//arising from the use of this software.

//Permission is granted to anyone to use this software for any purpose,
//including commercial applications, and to alter it and redistribute it
//freely, subject to the following restrictions:

   //1. The origin of this software must not be misrepresented; you must not
   //claim that you wrote the original software. If you use this software
   //in a product, an acknowledgment in the product documentation would be
   //appreciated but is not required.

   //2. Altered source versions must be plainly marked as such, and must not be
   //misrepresented as being the original software.

   //3. This notice may not be removed or altered from any source
   //distribution.
  
#include <iostream>
#include <XEDAL/PhysFS/sfmlphysfs.hpp>

//sf::physfs::physfs(const char *filename){
//    file = PHYSFS_openRead(filename);
//    error = false;
//    if (file == NULL){
//        std::cout << PHYSFS_getLastError() << std::endl;
//        error = true;
//    }
//}
//
//sf::physfs::~physfs(){
//    if (error){
//        return;}
//    if (PHYSFS_close(file) == 0 ){
//        std::cout << PHYSFS_getLastError() << std::endl;
//    }
//}
//
//sf::Int64 sf::physfs::Read(char *data, sf::Int64 size){
//    if (error){
//        return 0;}
//    sf::Int64 readed = PHYSFS_read(file, data, 1, size);
//    if (readed == -1){
//        std::cout << PHYSFS_getLastError() << std::endl;
//        return 0;
//    }
//    return readed;
//}
//
//sf::Int64 sf::physfs::Seek(sf::Int64 position){
//    if (error){
//        return -1;}
//    if ( PHYSFS_seek(file, position) == 0 ){
//        std::cout << PHYSFS_getLastError() << std::endl;
//        return -1;
//    }
//    return position;
//}
//
//sf::Int64 sf::physfs::Tell(){
//    if (error){
//        return -1;}
//    sf::Int64 position = PHYSFS_tell(file);
//    if (position == -1){
//        std::cout << PHYSFS_getLastError() << std::endl;
//    }
//    return position;
//}
//
//sf::Int64 sf::physfs::GetSize(){
//    if (error){
//        return -1;}
//    sf::Int64 size = PHYSFS_fileLength(file);
//    if (size == -1){
//        std::cout << PHYSFS_getLastError() << std::endl;
//    }
//    return size;
//}
