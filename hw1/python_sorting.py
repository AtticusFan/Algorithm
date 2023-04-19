with open('test1.txt', 'r') as file:
    data = [float(x) for x in file.read().split()]

#data = [1, 2, 4 ,3, 7, 6, 9, 8, -4, 3.4, 8.5, -9]
def InsertionSort(data):
    length = len(data)
    i=0
    while i<length:
        temp = data[i]
        j = i-1
        while j>=0 and temp<data[j]:
            data[j+1] = data[j]
            j-=1
        data[j+1] = temp
        i+=1
    return data
def Partition(data, start, end, size):
    pivot_index = start
    pivot = data[pivot_index]
    while start < end:
        while start < size and data[start] <= pivot:
            start+=1

        while data[end] > pivot:
            end-=1

        if start < end:
            data[start], data[end] = data[end], data[start]
            
    data[pivot_index], data[end] = data[end], data[pivot_index]
    return end
def QuickSort(data, start, end):
    if start < end:
        ptn = Partition(data, start, end, len(data))
        QuickSort(data, start, ptn-1) #left
        QuickSort(data, ptn+1, end)   #right
    return data

print("1.Quick Sort 2.Insertion Sort")
TypeOfSort = int(input("Enter type of sorting:"))
if TypeOfSort==1:
    print("Using Quick Sort...") 
    print("Result:", QuickSort(data, 0, len(data)-1))
    print("# of test data:", len(data))
    print("The smallest number:", data[0])
    print("The biggest number:", data[len(data)-1])
    file.close()
elif TypeOfSort==2:
    print("Using Insertion Sort...")
    print("Result:", InsertionSort(data))
    print("# of test data:", len(data))
    print("The smallest number:", data[0])
    print("The biggest number:", data[len(data)-1])
    file.close()
else:
    print("無此排序方法，請重新輸入。")