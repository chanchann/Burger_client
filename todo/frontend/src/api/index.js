import axios from 'axios'

const mockTodos = [
  {id: 1, text: 'Item 1', done: false},
  {id: 2, text: 'Item 2', done: true}
]

const mockRequest = ()=>{
    return new Promise((resolve, reject)=>{
        setTimeout(()=>{
            Math.random() < 0.85 ? resolve(mockTodos) : reject(new Error("Get Todo list error!"))
        }, 100)
    })
}
  

const api = axios.create({
    headers: {
      'Content-Type': 'application/json',
      'X-CSRF-TOKEN': document.querySelector('meta[name="csrf-token"]').getAttribute('content')}
    })
  