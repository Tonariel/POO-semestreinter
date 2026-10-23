
#ifndef CATALOG_HPP
#define CATALOG_HPP

#include <vector>
#include <memory>
#include <cstddef>
#include <utility>

template <typename T>
class Catalog {
private:
    std::vector<std::unique_ptr<T>> elements_;

public:
    // Constructeur et destructeur
    Catalog() = default;
    ~Catalog() = default;

    // Interdire la copie du catalogue
    Catalog(const Catalog&) = delete;
    Catalog& operator=(const Catalog&) = delete;

    // Autoriser le deplacement
    Catalog(Catalog&&) = default;
    Catalog& operator=(Catalog&&) = default;

    // Ajouter un objet
    void Add(std::unique_ptr<T> element) {
        elements_.push_back(std::move(element));
    }

    // Recuperer un objet par son indice
    T* Get(std::size_t index) {
        if (index >= elements_.size()) {
            return nullptr;
        }

        return elements_[index].get();
    }

    // Recuperer un objet depuis un catalogue constant
    const T* Get(std::size_t index) const {
        if (index >= elements_.size()) {
            return nullptr;
        }

        return elements_[index].get();
    }

    // Nombre d'objets
    std::size_t Size() const {
        return elements_.size();
    }

    // Verifier si le catalogue est vide
    bool Empty() const {
        return elements_.empty();
    }
};

#endif
