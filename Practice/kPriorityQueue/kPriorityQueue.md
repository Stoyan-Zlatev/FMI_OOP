  **Задача 2:**
 Създайте **шаблонна** опашка с k приоритета. При взимане на елемент от опашката трябва да се връща най-отдавна добавения елемент от тези с най-висок приоритет. **Важно:** Използвайте имплементацията на опашка от предната задача!
 
  ```c++
int main()
{
	kPriorityQueue<char> q(4); // 4 priorities - 0, 1, 2 и 3.
	
	q.push('A',0): //adds A with lowest priority: 0
	q.push('B',3);
	q.push('C',2);
	q.push('D',2);
	q.push('E',1);
	
	//q.push('F', 5); //error! No such priority!
	
	q.peek(); // B
	q.pop();
	
	q.peek(); // C
	q.pop();
	
	q.peek(); // D
	q.pop();
	
	q.peek(); // E
	q.pop();
	
	q.peek(); // A
	q.pop();
}
 ```
