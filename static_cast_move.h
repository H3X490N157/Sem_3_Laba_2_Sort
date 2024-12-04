#pragma once 

template<typename T>
T&& mover(T& in){
    return static_cast<T&&>(in); 
}

template<typename T>
T&& mover(T&& in){
    return static_cast<T&&>(in);
}