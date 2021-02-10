import React from 'react';
import axios from 'axios';
import {
    BrowserRouter as Router,
    Switch,
    Route,
    Redirect
  } from 'react-router-dom'
import './app2.css';

const Notfound = () => <Redirect to='/' />



class App extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            code: '',
            sucess: false,
            error: false
        };
        this.handleButton = this.handleButton.bind(this);
        this.handleChangeCode = this.handleChangeCode.bind(this);
        
    }

    handleChangeCode(event) {
        this.setState({code: event.target.value});
    }

    handleButton(event) {
        axios({
            method: 'POST',
            url: 'http://localhost:8080/permition/codigo',
            data: JSON.stringify({"codigo":this.state.code}), 
            headers: {
                "Content-Type": "application/json"
            }
        })
        .then(response => {
          this.setState({sucess: true, error:false})
        }) 
        .catch(response => {
          this.setState({error: true, sucess:false})
        })
    
        event.preventDefault();
    }


    handleChange = param => e => {
        
        axios({
            method: 'POST',
            url: 'http://localhost:8080/permition/codigo',
            data: JSON.stringify(param), 
            headers: {
                "Content-Type": "application/json"
            }
        })
        .then(response => {
          this.setState({sucess: true, error:false})
        }) 
        .catch(response => {
          this.setState({error: true, sucess:false})
        })
    
        e.preventDefault();
    };

    render1 = (router) => (
        <div style={{ textAlign: 'center' , paddingTop: '4%'}}>
        <h1>Atribuição de permissões</h1>
        <div class='box'>
            
        <div class='box-form'>
        
          <div class='box-login-tab'></div>
          <div class='box-login-title'>
            <div class='i i-login'></div><h2>SSI</h2>
          </div>
          <div class='box-login'>
            <div class='fieldset-body' id='login_form'>
                <button class='b b-form i i-more' title='Mais Informações'></button>
                  <p class='field'>
                <label for='pass'>CODIGO</label>
                <input class="input" type="code" value={this.state.code} className="form-control" id="codeInput" onChange={this.handleChangeCode} placeholder="Código" ></input>
              <span id='valida' class='i i-close'></span>
              {this.state.sucess === false & this.state.error === false? <p>Depois de 3 inserções - timeout 5s</p>: null}
                    {this.state.sucess? <p>Sucesso</p> : this.state.error? <p>Espere até 5 segundos</p>: null }
              </p>
                  <input class="btn" type='submit' onClick={this.handleButton} value="Enviar" /> 

            </div>
            
          </div>
        </div>
        </div>
        </div>
    )

   


    

    match = ({ match }) => (
        <div style={{ textAlign: 'center' , paddingTop: '4%'}}>
        <h1>Atribuição de permissões</h1>
        <div class='box'>
            
        <div class='box-form'>
        
          <div class='box-login-tab'></div>
          <div class='box-login-title'>
            <div class='i i-login'></div><h2>SSI</h2>
          </div>
          <div class='box-login'>
            <div class='fieldset-body' id='login_form'>
                <button class='b b-form i i-more' title='Mais Informações'></button>
                  <p class='field'>
                <label for='pass'>CODIGO</label>
                <input class="input" type="code" value={match.params.code} className="form-control" id="codeInput" onChange={this.handleChangeCode} placeholder="Código" ></input>
                   <span id='valida' class='i i-close'></span>
                   {this.state.sucess === false & this.state.error === false? <p>Depois de 3 inserções - timeout 5s</p>: null}
                    {this.state.sucess? <p>Sucesso</p> : this.state.error? <p>Espere até 5 segundos</p>: null }
              </p>
              <input class="btn" type='submit' onClick={this.handleChange({"codigo":match.params.code})} value="Enviar" />
                    </div>
          </div>
        </div>
        </div>
        </div>
      )
     


  render() {
    return (
        <div className="App">
            <Router>
                <Switch>
                    <Route path='/:code' component={this.match}/>
                    <Route exact path='/' component={this.render1}/>
                    <Route component={Notfound} />
                </Switch>
            </Router>
        </div>
    );
}
}

export default App;
