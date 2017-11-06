# Mines

## Краткое руководство 
Входные данные. Для инициализации виртуального поля требуется создать и заполнить файл по следующим правилам:
- На первой строчке пишем два числа через пробел: ширину и высоту поля.
- Следующая строчка уже является разметкой поля, а значит на место той ячейки, где есть мина, ставится `!`, на место неоткрытой ячейки - `?`, а туда, где должна быть подсказка - ячейка с числом мин вокруг, ставим соответствующее натуральное число.

Получится что-то вроде этого  
  3 3  
  ???  
  ?2!  
  ???  
Также необходимо указать выходной файл, в котором будет отображен результат работы программы. Формат выходных данных тоже достаочно прост: на месте мины, которая была определена во входном файле, так и останется `!`, на месте ячейки с числом мин тоже останется натуральное число, а неоткрытым ячейкам, к которым, разумеется, прилегает хотя бы одна подсказка, будут соотвествовать вероятности  нахождения мины в ячейке - вещественные числа в интервале `[0,1]`.  

## Немного теории
Методы, представленные ниже, конечно, никак не могут гарантировать стопроцентную победу, даже на уровне сложности "Новичок" попадаются неоднозначные случаи. Но играть можно по-разному: например, можно открывать только достоверные ячейки - те, в которых точно есть или точно нет мины, или же открывать поле в тех местах, где подсчитанная вероятность попадает в интервал `(0,1)`, обратите внимание на скобки.  
![](img/1.png)  
Рисунок 1 - Тот случай, когда можно однозначно определить расположение одной мины.  
![](img/2.png)   
Рисунок 2  - Учитывая, что одна мина уже определена, можно сказать, что нижняя ячейка безопасна.  

Эффективнее всего - комбинировать эти два способа, а именно: сначала проверить поле на тривиальные случаи, и если такие находятся, то делать ход, ничем при этом не рискуя и обновляя игровое поле. Но в 99 процентах случаев всю игру так пройти не получится, т.к. мы обязательно наткнемся на случай, когда наверняка мину или безопасную ячейку определить нельзя. Тогда в ход идет второй способ для расстановки вероятностей в доступные ячейки.  
Для этих двух способов реализованы разные алгоритмы.  

![](img/3.png)   
Рисунок 3  - Случай, когда придется применять второй алгоритм.  

## Первый алгоритм  

Он заключается в создании и преобразовании групп ячеек. Создаются группы достаочно просто - прилегающие к подсказке ячейке объединяются в одно множество. Далее следуют некоторые преобразования над группами, применимые в конкретных случаях.  

Для начала нужно преобразовать группы. Для этого:  

1. Сравниваем каждую группу с каждой последующей группой.  
2. Если группы одинаковые, то вторую удаляем.   
3. Если одна группа содержит другую, то вычитаем из большей меньшую. То есть было две группы `(5678,2)` и `(5,1)`, стало `(678,1)` и `(5,1)`; `(2345,3)` и `(5,1)` → `(234,2)` и `(5,1)`  
4. Пересекающиеся группы преобразовываем по следующему принципу:  
        - Создаем новую группу из пересекающихся ячеек  
        - Рассчитываем количество мин в новой группе, равное количеству мин в группе с большим числом мин минус оставшееся количество ячеек в другой группе после отделения пересекающихся ячеек.
        - Если результат не равен количеству мин в группе с меньшим количеством мин, то прекращаем преобразование  
        - Вычитаем из обоих пересекающихся групп новообразованную группу.
        - Добавляем новообразованную группу в список групп  
    Таким образом `(234,2) и (123,1) → (1,0) и (23,1) и (4,1)`.
5.Повторяем с п. 1 до тех пор, пока не будет производиться никаких изменений.  

На выходе мы должны получить нужные нам два множества групп: в котором количество ячеек равно количеств мин в группе и с нулевым числом мин в группе. Таким образом мы получим те группы, которые нужно целиком отмечать как мины и те, которые можно полностью открывать. Поле после этого обновляется, игровой процесс продвигается.   
Поговорим о сложности. Легче всего оценить сложность по памяти: одна группа содержит не более 8 ячеек, а значит требуется `O(1)` памяти для каждой группы. Всего неоткрытых ячеек - не более, чем `n*m`, а число групп не может быть больше числа ячеек, а значит имеем `O(n^2)` групп. Это и будет сложностью по памяти алгоритма. Время выполнения оценим следующим образом: метод групп во многом похож на матричный метод преобразования, поэтому чуть позже проведем аналогию.  
Вкратце о матричном методе: необходимо составить матрицу `t x m`, где `t` - число, отображаемое в ячейке-подсказке, `m` - число ячеек, к ней прилегающих. `t` и `m` меньше `n^2`, значит матрица по памяти будет занимать `O(n^4)`. Затем матрица преобразовывается по методу Гаусса, чтобы получить стопроцентную вероятность нахождения мины в какой-то ячейке, хотя такой ход событий возможен не всегда. Матричный метод выводит то же самое, что и метод групп. Сложность метода Гаусса для квадратной матрицы `n x n` известна - `O(n^3)`, тогда для матрицы `n^4` она составит `O(n^6)`.  
Метод групп в целом похож на матричный, поэтому сложность его тоже будет `O(n^6)`. 

## Второй алгоритм  

Этот метод универсален и применим для любых ситуаций, в том числе и тех, для которых существует первый метод. Но использование второго алгоритма для вышеописанных случаев не очень эффективно, хоть и уместно. Вероятность нахождения мины в свободной ячейке в случае, как на рисунке 1, будет в районе 0.99, потому что эта ячейка может впоследствии войти в несколько групп, и при корректировке вероятность изменится с ровно единицы на что-то более абстрактное.  
Алгоритм работает в два этапа:
- Определение вероятности в отдельных ячейках, учитывая влияние нескольких открытых ячеек
- Корректировка вероятностей, учитывая взаимное влияние групп с общими ячейками друг на друга   

Берем список всех групп и идем от начала списка к концу. Сначала расставляются вероятности по простому принципу: всем ячейкам в группе присваивается вероятность, равная количеству мин в группе, деленной на число ячеек в группе. Так происходит, пока не встречается ячейка, ранее обработанная в другой группе. Тогда вероятность корректруется по следующей формуле: `P = 1 - (1- NewVar)*(1-OldVar)`, где `OldVar` - значение вероятности, залитое в эту ячейку в предыдущей итерации, а `NewVar`- вероятность, посчитанная по тому же принципу, но для текущей группы. Эта операция выполняется за `O(1)` времени.  

Когда все группы заполнены вероятностями, следует проверка для каждой группы: `|∑Pi - M| <= Eps`, где `Pi` - вероятность i-ой ячейки группы, `M` - количество мин в группе, а `Eps` - некоторая заданная точность, которую я определил как 0.01. Если в какой-то группе условие не выполняется, то начинается корректировка по следующему принципу:  
Считается коэффициент корректиовки `Mlt = M / ∑Pi`, после чего вероятность каждой ячейки группы умножается на этот коэффициент. Не стоит забывать, что некоторые ячейки входят в несколько групп, а значит сумма вероятностей таким преобразованием меняется не только для обрабатываемой группе. Поэтому после того, как была преобразована "проблемная" группа, проверку опять следует начачать с самой первой группы в списке.  Сложность этого этапа по времени зависит от числа ячеек-подсказок, то есть `O(n^2)`.
Алгоритм закончится, когда все группы будут проверены, и условие будет выполняться в каждой из них.  

Сложность. На каждом шаге составляются уравнения, число которых равно мощности объединения всех групп. То есть `O(n^2)` уравнений. Все они решаются за константное время, потому что в каждой группе не более 8 ячеек, а значит не более 7 умножений дробей, содержащей не более 7 сложений. Тогда сложность коррекции - `O(n^2)`.  

Получаем окончательную сложность алгоритма в виде `O(n^2)`, т.к. в нем выполняются последовательно два этапа, каждый по `O(n^2)` времени.  

