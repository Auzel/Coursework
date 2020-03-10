var users=[];
numSales=0;
var trackFilter=[];

//calculate number of cart items
function calcCartNum(){
    readFromStorage();
    var pos=localStorage.currIndex;
    var sum=0;
    for(var i=0;i<users[pos].buyer.items.length;i++){
        sum+=Number(users[pos].buyer.items[i].quantity);
    }
    return sum;
}

/*Allows user to logout*/
function logout(){
 
   Object.keys(localStorage).forEach(function(key){
        if(key!="users"){
        localStorage.removeItem(key);
        };
    });

}


/*Dynamically generate Buy section When the user first goes on before filtering */
function initBuy(){ 
    var id,name,picture,category,listPrice,avgProdRating,description,sellerName,numSold;
    var elem, banner;
    var numResults=0;
    var disp=[];
    var e, order;
    var pos;

    readFromStorage();


    pos=localStorage.currIndex;
    document.getElementById('cartCount').innerHTML=calcCartNum();

    e=document.getElementById('sortPr');
    order=e.options[e.selectedIndex].value;    

    //so that search array is removed from local storage when loaded

    if(sessionStorage.getItem('found')!==null)
        sessionStorage.removeItem('found');
       
    

    var choice=document.querySelector('#tracker li:last-child').textContent;

    var banner=document.getElementById('bannerBuy');
    if(choice==='All')
        banner.innerHTML='All Products';
    else
        banner.innerHTML=choice;



    
    document.getElementById('products').innerHTML='';


    
    
    for(var i=0;i<users.length;i++){
        for(var j=0;j<users[i].seller.itemsForSale.length;j++){
            if(users[i].seller.itemsForSale[j]){
                id=users[i].seller.itemsForSale[j].id;
                name=users[i].seller.itemsForSale[j].name;
                picture=users[i].seller.itemsForSale[j].picture;
                category=users[i].seller.itemsForSale[j].category;                							                							
                listPrice=users[i].seller.itemsForSale[j].listPrice;
                avgProdRating=users[i].seller.itemsForSale[j].avgProdRating;
                description=users[i].seller.itemsForSale[j].description;
                sellerName=users[i].info.fName + ' ' + users[i].info.lName;
                numSold=users[i].seller.numSold;
            
                
                if(choice === 'All'){                    
                    disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                    numResults++;
                }
                else if(users[i].seller.itemsForSale[j].category === choice){    
                    disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                    numResults++;
                }       
                
            } 
        }
        
    }

    dynamicGen(disp,order);
    
    elem = document.getElementById('changeNum');
    elem.innerHTML=' '+numResults+'/'+numResults;

}


/*Allows user to search for products*/
function search(){
    var id,name,picture,category,listPrice,avgProdRating, description, sellerName, numSold;
    var disp=[];
    var numResults=0, elem;
    var found=[];
    var e, order;

    e=document.getElementById('sortPr');
    order=e.options[e.selectedIndex].value;

    var key=document.getElementById('searchBox').value;
    document.getElementById('products').innerHTML=''; 
    
    /*
    document.querySelectorAll('#formData input[type="radio"]').forEach(function(element){
        element.checked=false;
    }); 

    document.querySelectorAll('#formData input[type="number"]').forEach(function(element){
        element.value="";
    }); 
    */


    for(var i=0;i<users.length;i++){
        for(var j=0;j<users[i].seller.itemsForSale.length;j++){
            if(users[i].seller.itemsForSale[j]){
                if(users[i].seller.itemsForSale[j].name.toLowerCase().startsWith(key.toLowerCase())){
                    id=users[i].seller.itemsForSale[j].id;
                    name=users[i].seller.itemsForSale[j].name;
                    picture=users[i].seller.itemsForSale[j].picture;
                    category=users[i].seller.itemsForSale[j].category;                							                							
                    listPrice=users[i].seller.itemsForSale[j].listPrice;
                    avgProdRating=users[i].seller.itemsForSale[j].avgProdRating;
                    description=users[i].seller.itemsForSale[j].description;
                    sellerName=users[i].info.fName + ' ' + users[i].info.lName;
                    numSold=users[i].seller.numSold;
                    disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                    numResults++;
                    found.push(users[i].seller.itemsForSale[j].name);
                }

            }

        }
    }
    
    sessionStorage.found=found;

    dynamicGen(disp,order);
    elem = document.getElementById('changeNum');
    elem.innerHTML=' '+numResults+'/'+numResults;
   
    return false;
}

/*Allows user to filter prodcuts to buy*/
function filterBuy(){
    var id,name,picture,category,listPrice,avgProdRating,description,sellerName,numSold;
    var found, elem;
    var numResults=0;
    var disp=[];
    var e, order;

    
    
    e=document.getElementById('sortPr');
    order=e.options[e.selectedIndex].value;
    
    readFromStorage(); //to get users array of objects
   
  
    if(sessionStorage.getItem('found')!==null){
        found=sessionStorage.found;
        if(found===undefined){
            found=[];
        }

    }
    
    

    document.getElementById('products').innerHTML='';


    var own, priceStrt, priceEnd, choice;
    var x=document.querySelectorAll('#formData input[type=radio]');
    for(var i=0;i<4;i++){
        if(x[i].checked){
            own=x[i].value;
        }
    }

    var y=document.querySelectorAll('#formData input[type=number]');
    priceStrt=Number(y[0].value);
    priceEnd=Number(y[1].value);

    if(priceStrt==='')
        priceStrt=false;
    if(priceEnd==='')
        priceEnd=false;
    
    choice=document.querySelector('#tracker li:last-child').textContent;
   
    
    for(var i=0;i<users.length;i++){
        for(var j=0;j<users[i].seller.itemsForSale.length;j++){
            if(users[i].seller.itemsForSale[j]){
                id=users[i].seller.itemsForSale[j].id;
                name=users[i].seller.itemsForSale[j].name;
                picture=users[i].seller.itemsForSale[j].picture;
                category=users[i].seller.itemsForSale[j].category;                							                							
                listPrice=users[i].seller.itemsForSale[j].listPrice;
                avgProdRating=users[i].seller.itemsForSale[j].avgProdRating;
                description=users[i].seller.itemsForSale[j].description;
                sellerName=users[i].info.fName + ' ' + users[i].info.lName;
                numSold=users[i].seller.numSold;
             


                if(choice === 'All'){
                    
                    if(own && priceStrt && priceEnd){                        
                        if(users[i].seller.itemsForSale[j].ownLength === own 
                        && users[i].seller.itemsForSale[j].listPrice>=priceStrt 
                        && users[i].seller.itemsForSale[j].listPrice <= priceEnd){
                            
                            if(found!==undefined){
                                
                               if (found.includes(users[i].seller.itemsForSale[j].name)){
                                    disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });          
                                    numResults++;
                               }
                            }
                            else{
                                disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                numResults++;
                            }                    
                            
                        }
                    } 
                    else if (own && priceStrt && !priceEnd){
                        if(users[i].seller.itemsForSale[j].ownLength === own 
                        && users[i].seller.itemsForSale[j].listPrice>=priceStrt){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                            else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }       

                        }
    
                    }
                    else if(own && !priceStrt && priceEnd){               
                        if(users[i].seller.itemsForSale[j].ownLength === own 
                        && users[i].seller.itemsForSale[j].listPrice<=priceEnd){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                            else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }       
                        }
                    }
                    else if(own && !priceStrt && !priceEnd){                     
                        if(users[i].seller.itemsForSale[j].ownLength === own){  
                                         
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                             }
                            else{   
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }       
                            
                        }
                    }
                    else if(!own && priceStrt && priceEnd){
                        if(users[i].seller.itemsForSale[j].listPrice>=priceStrt 
                        && users[i].seller.itemsForSale[j].listPrice <= priceEnd){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                             else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }       
                        }
    
                    }
                    else if(!own && priceStrt && !priceEnd){
                        if(users[i].seller.itemsForSale[j].listPrice>=priceStrt){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                             else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }    
                         }
                    }
                    else if(!own && !priceStrt && priceEnd){
                        if(users[i].seller.itemsForSale[j].listPrice<=priceEnd){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                            else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }    
                        }
                    }
                    else if(!own && !priceStrt && !priceEnd){
                        if(found!==undefined){
                            if (found.includes(users[i].seller.itemsForSale[j].name)){
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                 numResults++;
                            }
                        }
                        else{
                            initBuy();
                            return; 
                        }    
                        
                    }

                }
                else if (users[i].seller.itemsForSale[j].category === choice){
                    if(own && priceStrt && priceEnd){
                        if(users[i].seller.itemsForSale[j].ownLength === own 
                        && users[i].seller.itemsForSale[j].listPrice>=priceStrt 
                        && users[i].seller.itemsForSale[j].listPrice <= priceEnd){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                            else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }  
                        }
                    } 
                    else if (own && priceStrt && !priceEnd){
                        if(users[i].seller.itemsForSale[j].ownLength === own 
                        && users[i].seller.itemsForSale[j].listPrice>=priceStrt){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                            else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }  
                        }
    
                    }
                    else if(own && !priceStrt && priceEnd){
                        if(users[i].seller.itemsForSale[j].ownLength === own 
                        && users[i].seller.itemsForSale[j].listPrice<=priceEnd){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                            else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }  
                        }
                    }
                    else if(own && !priceStrt && !priceEnd){
                        if(users[i].seller.itemsForSale[j].ownLength === own){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                            else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }  
                        }
                    }
                    else if(!own && priceStrt && priceEnd){
                        if(users[i].seller.itemsForSale[j].listPrice>=priceStrt 
                        && users[i].seller.itemsForSale[j].listPrice <= priceEnd){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                            else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }  
                        }
    
                    }
                    else if(!own && priceStrt && !priceEnd){
                        if(users[i].seller.itemsForSale[j].listPrice>=priceStrt){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                            else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }  
                         }
                    }
                    else if(!own && !priceStrt && priceEnd){
                        if(users[i].seller.itemsForSale[j].listPrice<=priceEnd){
                            if(found!==undefined){
                                if (found.includes(users[i].seller.itemsForSale[j].name)){
                                     disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                     numResults++;
                                }
                            }
                            else{
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });  
                                 numResults++;
                            }  
                        }
                    }
                    else if(!own && !priceStrt && !priceEnd){
                        if(found!==undefined){
                            if (found.includes(users[i].seller.itemsForSale[j].name)){
                                 disp.push({'id': id, 'name': name, 'category': category, 'picture':picture, 'listPrice':listPrice, 'avgProdRating':avgProdRating, 'description':description, 'sellerName':sellerName, 'numSold':numSold });
                                 numResults++;
                            }
                        }
                        else{
                            initBuy();
                            return; 
                        } 
                       
                    }

                }
           
            }
    
        }
    
    } 
    
    dynamicGen(disp,order);       
    elem = document.getElementById('changeNum');
    elem.innerHTML=' '+numResults+'/'+numResults;
}


/*function that dyanmically generate all webpages when called*/
function dynamicGen(disp,order){
    var id,name,category,picture,listPrice,avgProdRating,description,sellerName,numSold;

    if(order==='Name'){
        //sort by name
        disp.sort(function(a, b) {
            if(a.name<b.name)
                return -1;
            else if(a.name>b.name)
                return 1;
            return 0;
        });
    } 
    
    else if(order==='Cust Rating'){
        //sort by avg customer rating
        disp.sort(function(a, b) {
            if(Number(a.avgProdRating)<Number(b.avgProdRating))
                return -1;
            else if(Number(a.avgProdRating)>Number(b.avgProdRating))
                return 1;
            return 0;
        });
    }
    else if(order==='Price L-W'){
        //sort by price ascending
        disp.sort(function(a, b) {
            if(Number(a.listPrice)<Number(b.listPrice))
                return -1;
            else if(Number(a.listPrice)>Number(b.listPrice))
                return 1;
            return 0;
        });
    } 
    else if(order==='Price H-L'){
        //sort by price descending
        disp.sort(function(a, b) {
        if(Number(a.listPrice)>Number(b.listPrice))
            return -1;
        else if(Number(a.listPrice)<Number(b.listPrice))
            return 1;
        return 0;
        });
    }    
    


    for(var i=0;i<disp.length;i++){
        id=disp[i].id;
        name=disp[i].name;
        category=disp[i].category;
        picture=disp[i].picture;
        listPrice=disp[i].listPrice;
        avgProdRating=disp[i].avgProdRating;
        description=disp[i].description;
        sellerName=disp[i].sellerName;
        numSold=disp[i].numSold;
        

        var star=[];
    

        document.getElementById('products').innerHTML+=
        '<figure>'
        +' <a href="Product.html" onclick="newWebPage(\''+id+'\',\''+name+'\',\''+category+'\',\''+picture+'\',\''+listPrice+'\',\''+avgProdRating+'\',\''+description+'\',\''+sellerName+'\',\''+numSold+'\');"> '
        +'		<img src="'+picture+'" alt="picture of '+name+'"> '
        +'		<figcaption>'
        +'			<span class="title">'+name+'</span> '
        +'		</figcaption> '
        +'	</a> '
        +'	<div class="starRating"> '
        +'		<span class="fa fa-star"></span> '
        +'		<span class="fa fa-star"></span> '
        +'		<span class="fa fa-star"></span> '
        +'		<span class="fa fa-star"></span> '
        +'		<span class="fa fa-star"></span> '
        +'	</div> '
        +'	<div class="cost"> $'+listPrice+'</div> '
        +'</figure> ';					

        /*calculates number of average Product Ratin Stars*/
        star=document.querySelectorAll('.starRating span');                    
                    
        for(var k=star.length-5;k<star.length-5+avgProdRating;k++){
          
            star[k].classList.add('checked');			
        }

    }

    

}

//Store informaiton for later use by product webpage
function newWebPage(id,name, category, picture, listPrice,avgProdRating,description,sellerName,numSold){
    var obj={id:id, title:name, category:category, img:picture, cost:listPrice, avgProdRating:avgProdRating, description:description, sellerName:sellerName, numSold:numSold};
    localStorage.productDyn=JSON.stringify(obj);
}

//allows user to add an item to cart

function addToCartMain(){
    var pos;
    var id,name,picture,category, description,quantity,listPrice,avgProdRating,ownLength;
    var e, quant;
    readFromStorage();
    pos=localStorage.currIndex;

    id=document.getElementById('bookIdPr').textContent;

    e=document.getElementById('selectPr');
    quantity=e.options[e.selectedIndex].value;   

 
    //now search through seller array for id and get the relevant info

    for (var i=0;i<users.length;i++){
        for(var j=0;j<users[i].seller.itemsForSale.length;j++){
            if(users[i].seller.itemsForSale[j].id == id){
                name=users[i].seller.itemsForSale[j].name;
                quant= users[i].seller.itemsForSale[j].quantity;

                if(Number(quantity)>Number(quant)){
                    alert(name+' can not be added be added to cart because the quantity chosen exceeds the quantity in stock of '+Number(quant)+'.');
                    return false;
                }
                   
                else {                    
                    picture=users[i].seller.itemsForSale[j].picture;
                    category=users[i].seller.itemsForSale[j].category;
                    description=users[i].seller.itemsForSale[j].description;                
                    listPrice=users[i].seller.itemsForSale[j].listPrice;
                    avgProdRating=users[i].seller.itemsForSale[j].avgProdRating;
                    ownLength=users[i].seller.itemsForSale[j].ownLength;
                }
               

            }
        }        
    }

    users[pos].buyer.addToCart(id,name,picture,category, description,quantity,listPrice,avgProdRating,ownLength);
    writetoStorage(); 
    
    alert(name+' has been added to cart.');
    return true;
}


//sell
function saleOfItem(){
   
    var arr1=document.querySelectorAll('#sellForm input[type="text"],#sellForm input[type="number"]');
  
    for(var i=0; i<arr1.length;i++){
        if(!arr1[i].value){
           alert('All fields are mandatory. Kindly fill out the remaining fields.');
            
           return false;
        
        }
    }

    if(!localStorage.recentImage){
        alert('You must include a picture of your item that is for sale.')
        return false;
    }


    var pos,id,name,picture,category, description,quantity,listPrice,ownLength;

    readFromStorage();

    if(localStorage.numSales){
        numSales=localStorage.numSales;
        id=1000+numSales;
        numSales++;
    } else {
        id=1000;  // start id number of books to be sold at 1000;
        numSales=1;  //set number of sales done on website to 1
    }

    localStorage.numSales=numSales;
    
    pos=localStorage.currIndex;
    name=document.getElementById('prodNameSe').value;
    picture=localStorage.recentImage;
    var e=document.getElementById('catSe');
    category=e.options[e.selectedIndex].value;    
    description=document.getElementById('detailsSe').value;
    quantity=document.getElementById('quantSe').value
    listPrice=document.getElementById('priceSe').value;
    ownLength=document.getElementById('ownLengthSe').value;
    
   

    users[pos].seller.addItemForSale(id,name,picture,category,description,quantity,listPrice,ownLength);
   

    writetoStorage();
    localStorage.removeItem('recentImage');

    if(confirm(name+" has been added to our catalogue on our products page. Click Okay to visit our Products page or Cancel to sell another product."))
        window.open('Buy.html','_self');
    else 
        window.open('Sell.html','_self');

    return true;

}

/*allows new user to be added to system*/
function register(e){
    readFromStorage();

    e.preventDefault(); 

    //use paramters to send info i would like to put
    var fName=document.getElementById('fNameReg').value;
    var lName=document.getElementById('lNameReg').value;
    var uName=document.getElementById('uNameReg').value.toLowerCase();
    var pword=document.getElementById('pwordReg').value;
    var pword2=document.getElementById('pwordReg1').value;

  
    for(var i=0;i<users.length;i++){
        if(users[i].info.userName===uName){
            alert('Username already exists');
            return false;
        } else if(pword!=pword2){
            alert('Password does not match. Please re-enter.');
            return false;
        }
    }

    users.push(new User(fName,lName,'',0,uName,pword));
    writetoStorage();
    if(confirm("You have successfully registered. Click Okay to proceed to the login Page or Cancel to create another account."))
        window.open('Login.html','_self');
    else 
        window.open('Registration.html','_self');


    return true;
}

/*allows user to be log in to the system*/
function login(e){

    Object.keys(localStorage).forEach(function(key){
        if(key!="users"){
        localStorage.removeItem(key);
        };
    });

    readFromStorage();

    e.preventDefault(); 

    var uName=document.getElementById('uNameLog').value;
    var pword=document.getElementById('pwordLog').value;

    //check if length of uname or password is null
    
    for(var i=0;i<users.length;i++){
        if(users[i].info.userName===uName && users[i].info.password===pword){
            alert('Welcome '+users[i].info.fName+' '+users[i].info.lName);
            window.open('Buy.html','_self');
            localStorage.currIndex=i;
            return true;
        }
    }
    alert('Incorrect username/password'); 
    return false;
}


//store users array
function writetoStorage(){
    var str=JSON.stringify(users,function(key,value){
        if (typeof value==='function')
            return '/Function('+value.toString()+')/';
    return value;
    });
    localStorage.users=str;
}

//read users array from html storage
function readFromStorage(){
    if(localStorage.users){
        var str=localStorage.users;
        users=JSON.parse(str,function(key,value){
        if(typeof value==='string' && value.startsWith('/Function(') && value.endsWith(')/')){
            value=value.substring(10,value.length-2);
            return eval('('+value+')');
        }
        return value;
        });

    }
    
}


//Below are blueprints ; from which objects are instantiated
var User = function (fName,lName,lastVisit,numVisits,userName,password) {
    //implement paraneters here
    this.info=new Info(fName,lName,lastVisit,numVisits,userName,password);
    this.buyer=new Buyer();
    this.seller=new Seller();
};


var Info=function(fName,lName,lastVisit,numVisits,userName,password){
    this.fName=fName; 
    this.lName=lName;
    this.lastVisit=lastVisit;
    this.numVisits=numVisits;
    this.userName=userName;
    this.password=password;
}


var Buyer= function(){
    this.items=[];
    this.total=0;
    this.addToCart=function(id,name,picture,category, description,quantity,listPrice,avgProdRating,ownLength){
        
        this.items.push(new Item(id,name,picture,category, description,quantity,listPrice,avgProdRating,ownLength));
        this.total+=quantity*listPrice; 
    };

    this.purchased=[];

    this.checkout=function(id){
        
        this.purchased.push(this.removeFromCart(id)[0]);

    }

    this.removeFromCart=function(id){
        if(this.items){
            for(var i=0; i<this.items.length;i++){
                if(this.items[i].id===id){
                    this.total-=this.items[i].price;
                    return this.items.splice(i,1);
                    
                }
            } 
        }
    }

};


var Seller=function(){
    this.itemsForSale=[];
    this.itemsSold=[];
    this.numSold=0;
    this.salesAmt=0;
    this.addItemForSale=function(id,name,picture,category, description,quantity,listPrice,ownLength){
        this.itemsForSale.push(new Item(id,name,picture,category, description,quantity,listPrice,0,ownLength));
    };
   
    this.sellItem=function(id,quantity){
        var found=false;
        var pos, temp;
        
        if(this.itemsForSale){
            for(var i=0; i<this.itemsForSale.length;i++){
                if(this.itemsForSale[i].id==id){
                    this.numSold+=Number(quantity);
                    this.salesAmt+=this.itemsForSale[i].listPrice*quantity;
                    
                    if(this.itemsSold){
                        for(var k=0;k<this.itemsSold.length;k++){
                            if (this.itemsSold[k].id==id){
                                found=true;
                                pos=k;
                            }
                        }
                    }
                    if(found){
                        this.itemsSold[pos].quantity+=1;
                        this.itemsForSale[i].quantity-=1;
                    } else {
                        temp=JSON.parse(JSON.stringify(this.itemsForSale));
                        this.itemsSold.push(temp[i]); 
                        this.itemsSold[this.itemsSold.length-1].quantity=quantity;
                        this.itemsSold[this.itemsSold.length-1].price=this.itemsSold[this.itemsSold.length-1].quantity*this.itemsSold[this.itemsSold.length-1].listPrice;
                        this.itemsForSale[i].quantity-=quantity;
                    }
                    if(this.itemsForSale[i].quantity<=0)
                        this.itemsForSale.splice(i,1)[0];
                }
            }            
                      
        }          
    }; 

    var total=0;
    var count=0;
    this.addRating=function(rating){
        count++;
        total+=rating;
        this.avgSellerRating=Math.round(total/count);
    }

}


var Item= function(id,name,picture,category, description,quantity,listPrice,avgProdRating,ownLength,rating){
    this.id=id;
    this.name=name;
    this.picture=picture;
    this.category=category;
    this.description=description;
    this.quantity=quantity;
    this.listPrice=listPrice;
    this.price=quantity*listPrice;
    this.avgProdRating=avgProdRating;
    this.ownLength=ownLength; //Come back ..Follow along how program should flow
    this.rating=rating;

};




