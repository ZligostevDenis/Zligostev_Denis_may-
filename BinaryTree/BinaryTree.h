#ifndef BINARYTREE_H
#define BINARYTREE_H
#pragma once
#include <vector>
#include <queue>
#include <string>

struct Tree {  // Структура для представления узла бинарного дерева
    int data;
    Tree* left;
    Tree* right;
    Tree* parent;

    Tree(int val, Tree* par, Tree* l, Tree* r) { // Конструктор с указанием значения, родителя, левого и правого потомка
        data = val;
        left = l;
        right = r;
        parent = par;
    }

    Tree(int val) {  // Конструктор с указанием значения (родитель и потомки - nullptr)
        this->data = val;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }

    Tree() {  // Конструктор по умолчанию (значение -2000, указатели - nullptr)
        data = -2000;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    Tree* minTree(Tree* tree) {  // Находит узел с минимальным значением в поддереве
        if (tree->left == nullptr) return this;
        return tree->left->minTree(tree->left);
    }

    Tree* maxTree(Tree* tree) {   // Находит узел с минимальным значением в поддереве
        if (tree->right == nullptr) return this;
        return tree->right->minTree(tree->right);
    }

    void insert(int val) {   // Вставляет новое значение в дерево
        Tree* temp_tree = this;
        while (temp_tree != nullptr) {
            if (val > temp_tree->data) {   // Если значение больше, идем вправо
                if (temp_tree->right != nullptr)
                    temp_tree = temp_tree->right;
                else {  // Если правого потомка нет, вставляем здесь
                    Tree* tmp = new Tree(val);
                    tmp->parent = temp_tree;
                    temp_tree->right = tmp;
                    break;
                }
            }
            else if (val < temp_tree->data) {  // Если значение меньше, идем влево
                if (temp_tree->left != nullptr)
                    temp_tree = temp_tree->left;
                else {   // Если левого потомка нет, вставляем здесь
                    Tree* tmp = new Tree(val);
                    tmp->parent = temp_tree;
                    temp_tree->left = tmp;
                    break;
                }
            }
            else
                break;  // Если значение равно, ничего не делаем (дубликаты не допускаются)
        }
    }

    Tree* find(int val) {  // Ищет узел с заданным значением
        if (this == nullptr)  // Если дерево пусто, возвращаем nullptr
            return nullptr;
        if (this->data == val)  // Если значение найдено, возвращаем узел
            return this;
        else if (val < this->data)  // Иначе рекурсивно ищем в левом или правом поддереве
            return this->left->find(val);
        else if (val > this->data)
            return this->right->find(val);
    }

    bool erase(int val) {
        Tree* node = this->find(val);  // 1. Находим узел, который нужно удалить
        if (node == nullptr) return false; // 2. Если узел не найден, возвращаем false (нечего удалять)

        // Случай 1: Удаляемый узел - лист (нет потомков)
        if ((node->left == nullptr) && (node->right == nullptr)) {
            Tree* node_par = node->parent; // 3. Получаем родительский узел
            if (node_par->left == node)      // 4. Если удаляемый узел - левый потомок родителя
                node->parent->left = nullptr; // 5. Обнуляем указатель на левого потомка у родителя
            else                            // 6. Иначе, он правый потомок
                node->parent->right = nullptr; // 7. Обнуляем указатель на правого потомка у родителя
            delete node;                     // 8. Удаляем узел из памяти
        }
        // Случай 2: Удаляемый узел имеет одного потомка (левого или правого)
        else if ((node->left == nullptr && node->right != nullptr) ||
                 (node->left != nullptr && node->right == nullptr)) {
            Tree* node_par = node->parent; // 9. Получаем родительский узел
            if (node->left == nullptr) {   // 10. Если левого потомка нет
                if (node_par->left == node) // 11. Если удаляемый узел - левый потомок родителя
                    node->parent->left = node->right; // 12. Заменяем ссылку на удаляемый узел ссылкой на его правого потомка
                else
                    node->parent->right = node->right; // 13. Аналогично для правого потомка
                node->right->parent = node->parent;  // 14. Обновляем родителя для правого потомка (теперь он связан с родителем удаляемого узла)
            }
            else {                          // 15. Аналогичные действия, если правого потомка нет, а левый есть
                if (node_par->left == node)
                    node->parent->left = node->left;
                else
                    node->parent->right = node->left;
                node->left->parent = node->parent;
            }
            delete node;                 // 16. Удаляем узел из памяти
        }
        // Случай 3: Удаляемый узел имеет обоих потомков
        else {
            Tree* r_tree_min = node->right->minTree(node->right); // 17. Находим минимальный узел в правом поддереве удаляемого узла
            if (r_tree_min->left == nullptr && r_tree_min->right == nullptr) { // 18. Если минимальный узел - лист
                int tmp = r_tree_min->data;                         // 19. Сохраняем его значение
                this->erase(r_tree_min->data);                    // 20. Удаляем минимальный узел (как лист, используя Случай 1)
                node->data = tmp;                                 // 21. Заменяем значение удаляемого узла на значение минимального
            }
            else {  // 22. Если минимальный узел имеет правого потомка (он не может иметь левого, так как он минимальный)
                int tmp = r_tree_min->data;
                this->erase(r_tree_min->data); // 23. Удаляем минимальный узел (как узел с одним потомком, используя Случай 2)
                node->data = tmp;             // 24. Заменяем значение удаляемого узла на значение минимального
            }
        }
        return true; // 25. Узел успешно удален
    }

    void clear() {  // Рекурсивное удаление всех узлов дерева (очистка дерева)
        if(this != nullptr) {
            this->left->clear();
            this->right->clear();
            delete this;
            return;
        }
        else
            return;
    }

    void balance() {  // Балансировка дерева (преобразование в сбалансированное BST)
        std::vector<int> values;
        inorderTraversal(this, values);
        Tree* balancedTree = buildBalancedTree(values, 0, values.size() - 1);
        *this = *balancedTree;
    }

    void inorderTraversal(Tree* node, std::vector<int>& values){  // Вспомогательный метод: симметричный обход дерева для получения отсортированных значений
        if (node == nullptr)
            return;
        inorderTraversal(node->left, values);
        values.push_back(node->data);
        inorderTraversal(node->right, values);
    }

    Tree* buildBalancedTree(const std::vector<int>& values, int start, int end) {  // Вспомогательный метод: построение сбалансированного BST из отсортированного вектора
        if (start > end)
            return nullptr;  //  Базовый случай: пустое поддерево (если start > end)
        int mid = (start + end) / 2;  //  Находим средний элемент (корень поддерева)
        Tree* newNode = new Tree(values[mid]); //  Создаем новый узел с этим значением
        newNode->left = buildBalancedTree(values, start, mid - 1);  // Рекурсивно строим левое поддерево
        if (newNode->left != nullptr)
            newNode->left->parent = newNode;
        newNode->right = buildBalancedTree(values, mid + 1, end);  // Рекурсивно строим правое поддерево
        if (newNode->right != nullptr)
            newNode->right->parent = newNode;
        return newNode;  //  Возвращаем корень построенного поддерева
    }
};

struct BinaryTree {
    Tree* root; // 1. Указатель на корневой узел дерева

    // Конструктор по умолчанию (создает пустое дерево)
    BinaryTree() {
        root = nullptr; // 2. Инициализация корневого узла нулевым указателем (дерево пустое)
    }

    // Конструктор с начальным значением (создает дерево с одним узлом)
    BinaryTree(int val) {
        root = new Tree(val, nullptr, nullptr, nullptr); // 3. Создание корневого узла с заданным значением и нулевыми дочерними узлами и родителем
    }

    // Вставка значения в дерево
    void insert(int val) {
        this->root->insert(val); // 4. Вызов метода insert() для корневого узла, который рекурсивно вставит значение в нужное место в дереве
    }

    // Поиск узла по значению
    Tree* find(int val) {
        return (this->root->find(val)); // 5. Вызов метода find() для корневого узла, который рекурсивно найдет узел с заданным значением (или вернет nullptr, если узел не найден)
    }

    // Удаление узла по значению
    bool erase(int val) {
        return (this->root->erase(val)); // 6. Вызов метода erase() для корневого узла, который рекурсивно удалит узел с заданным значением (и вернет true, если удаление успешно)
    }

    // Балансировка дерева
    void balance() {
        if(this->root != nullptr) // 7. Проверка, не пустое ли дерево
            this->root->balance(); // 8. Вызов метода balance() для корневого узла, который сбалансирует дерево
    }

    // Очистка дерева (удаление всех узлов)
    void clear() {
        this->root->clear(); // 9. Вызов метода clear() для корневого узла, который рекурсивно удалит все узлы в дереве
        this->root = nullptr; // 10. Установка корневого узла в nullptr, чтобы обозначить, что дерево пустое
    }
};
#endif // BINARYTREE_H
